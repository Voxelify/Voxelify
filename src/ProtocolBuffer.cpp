/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#include <protocol/ProtocolBuffer.hpp>

#define ntohll(y) ( ( (uint64_t)ntohl(y) ) << 32UL | ntohl( y >> 32UL ) )
#define htonll(y) ntohll(y)
#define betole(x) ( ( (x & 0x00FF) << 8 ) | ((x & 0xFF00 ) >> 8 ) )

/**
 * Convert an UTF8 String to an UTF16 String BigEndian.
 *
 * @param source the source of the characters
 * @param dest the destination of the characters
 */
static unsigned int UTF8ToUTF16(unsigned char *source, unsigned short *dest)
{
	unsigned int offset = 0;
	unsigned int cur_pos = 0;
	unsigned int cp;

	while (*(source + offset) != '\0') {
		if (offset == UINT_MAX) {
			return -1;
		}
		if ((*(source + offset) & 0xF0) == 0xF0) {
			if (((*(source + offset + 1) & 0x80) != 0x80)
			    && ((*(source + offset + 2) & 0x80) != 0x80)
			    && ((*(source + offset + 3) & 0x80) != 0x80)) {
				return -1;
			}
			cp = (((((*(source + offset) & 0x7) << 2)
			        | ((*(source + offset + 1) & 0x30) >> 4))) << 16)
			     | ((((*(source + offset + 1) & 0xF) << 4)
			         | ((*(source + offset + 2) & 0x3C) >> 2)) << 8)
			     | (((*(source + offset + 2) & 0x3) << 6)
			        | (*(source + offset + 3) & 0x3F));
			offset += 4;
		} else if ((*(source + offset) & 0xE0) == 0xE0) {
			if (((*(source + offset + 1) & 0x80) != 0x80)
			    && ((*(source + offset + 2) & 0x80) != 0x80)) {
				return -1;
			}
			cp = ((((*(source + offset) & 0xF) << 4)
			       | ((*(source + offset + 1) & 0x3C) >> 2)) << 8)
			     | ((*(source + offset + 1) & 0x3) << 6)
			     | (*(source + offset + 2) & 0x3F);
			offset += 3;
		} else if ((*(source + offset) & 0xC0) == 0xC0) {
			if ((*(source + offset + 1) & 0x80) != 0x80) {
				return -1;
			}
			cp = (((*(source + offset) & 0x1F) >> 2) << 8)
			     | (((*(source + offset) & 0x3) << 6)
			        | (*(source + offset + 1) & 0x3F));
			offset += 2;
			if (cp <= 127) {
				return -1;
			}
		} else if (*(source + offset) <= 127) {
			cp = *(source + offset++);
		} else {
			return -1;
		}
		if (cp > 0xFFFF) {
			dest[cur_pos] = betole( 0xD800 + ( ( cp - 0x10000 ) >> 10 ));
			dest[cur_pos + 1] = betole( 0xD800 + ( ( cp - 0x10000 ) & 0x3FF ));
			cur_pos += 2;
		} else {
			dest[cur_pos++] = betole(cp);
		}
	}
	dest[cur_pos] = '\00';
	return 0;
}

ProtocolBuffer::ProtocolBuffer(boost::asio::streambuf &buffer) :
	output(buffer), socket(NULL)
{
}

ProtocolBuffer::ProtocolBuffer(boost::asio::ip::tcp::socket &socket) :
	output(NULL), socket(socket)
{
}

ProtocolBuffer &ProtocolBuffer::operator>>(unsigned char **value)
{
	unsigned short length;
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(&length), 0x2));
	length = ntohs(length);

	*value = new unsigned char[length];
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(*value), length));
	//TODO: UTF16 To UTF8 (Is is harm?)

	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator>>(unsigned char &value)
{
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(&value), 0x1));
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator>>(bool &value)
{
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(&value), 0x1));
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator>>(unsigned short &value)
{
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(&value), 0x2));
	value = ntohs(value);
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator >>(unsigned int **value)
{
	unsigned char length;
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(&length), 0x1));

	*value = new unsigned int[length];
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(*value), length * 0x4));
	for (int i = 0; i < length; i++) {
		*value[i] = ntohl(*value[i]);
	}

	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator>>(unsigned int &value)
{
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(&value), 0x4));
	value = ntohl(value);
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator>>(unsigned long &value)
{
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(&value), 0x8));
	value = ntohll(value);
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator>>(float &value)
{
	union {
		uint32_t intval;
		float dval;
		char buf[4];
	} float_type;
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(&float_type.buf), 0x4));
	value = ntohl(float_type.intval);
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator>>(double &value)
{
	union {
		uint64_t intval;
		double dval;
		char buf[8];
	} double_type;
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(&double_type.buf),
	                                      0x8));
	value = ntohll(double_type.intval);
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator>>(std::string &value)
{
	unsigned int size = 0;
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(&size), 0x2));

	char retVal[size];
	boost::asio::read(*socket,
	                  boost::asio::buffer(reinterpret_cast<char *>(&retVal), size));
	value.assign(retVal, size);

	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator<<(unsigned char value)
{
	output->sputn(reinterpret_cast<char *>(&value), 0x1);

	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator<<(bool value)
{
	char holder = (value == true ? 1 : 0);
	output->sputn(reinterpret_cast<char *>(&holder), 0x1);
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator<<(unsigned short value)
{
	unsigned short data = htons(value);
	output->sputn(reinterpret_cast<char *>(&data), 0x2);
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator<<(unsigned int value)
{
	unsigned int data = htonl(value);
	output->sputn(reinterpret_cast<char *>(&data), 0x4);
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator<<(unsigned long value)
{
	unsigned long data = htonll(value);
	output->sputn(reinterpret_cast<char *>(&data), 0x8);
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator<<(float value)
{
	union {
		uint32_t intval;
		float dval;
		char buf[4];
	} float_type;

	float_type.dval = value;
	float_type.intval = htonl(value);
	output->sputn(reinterpret_cast<char *>(&float_type.buf), 0x4);
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator<<(double value)
{
	union {
		uint64_t intval;
		double dval;
		char buf[8];
	} double_type;

	double_type.dval = value;
	double_type.intval = htonll((uint64_t)value);
	output->sputn(reinterpret_cast<char *>(&double_type.buf), 0x8);
	return *this;
}

ProtocolBuffer &ProtocolBuffer::operator<<(std::string value)
{
	unsigned short length = htons(value.length());
	output->sputn(reinterpret_cast<char *>(&length), 0x2);

	unsigned short wBuffer[length * 2];
	UTF8ToUTF16((unsigned char *) value.data(), (unsigned short *) &wBuffer);

	output->sputn(reinterpret_cast<char *>(&wBuffer), value.length() * 2);
	return *this;
}
