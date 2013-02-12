/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _PROTOCOL_BUFFER_HPP_
#define _PROTOCOL_BUFFER_HPP_

#include <boost/asio.hpp>

/**
 * Encapsulate the buffer for the protocol messages. The protocol
 * uses Big Endianess.
 */
class ProtocolBuffer
{
public:
	/**
	 * Constructor as an output stream.
	 *
	 * @param buffer the buffer that will contain the data
	 */
	ProtocolBuffer(boost::asio::streambuf &buffer);
	/**
	 * Constructor as an input stream.
	 *
	 * @param socket the socket to fetch the data from
	 */
	ProtocolBuffer(boost::asio::ip::tcp::socket &socket);

	/**
	 * Writes an unsigned character (8 Bits)
	 */
	ProtocolBuffer &operator <<(unsigned char value);

	/**
	 * Writes a boolean (8 Bits)
	 */
	ProtocolBuffer &operator <<(bool value);

	/**
	 * Writes an unsigned short (16 Bits)
	 */
	ProtocolBuffer &operator <<(unsigned short value);

	/**
	 * Writes an unsigned integer (32 Bits)
	 */
	ProtocolBuffer &operator <<(unsigned int value);

	/**
	 * Writes an unsigned long (64 Bits)
	 */
	ProtocolBuffer &operator <<(unsigned long value);

	/**
	 * Writes a float (32 Bits)
	 */
	ProtocolBuffer &operator <<(float value);

	/**
	 * Writes a double (64 Bits)
	 */
	ProtocolBuffer &operator <<(double value);

	/**
	 * Writes a UTF-16 string
	 */
	ProtocolBuffer &operator <<(std::string &value);

	/**
	 * Reads an array of bytes (16 Bits + length of the array)
	 */
	ProtocolBuffer &operator >>(unsigned char **value);

	/**
	 * Reads an unsigned character (8 Bits)
	 */
	ProtocolBuffer &operator >>(unsigned char &value);

	/**
	 * Reads a boolean (8 Bits)
	 */
	ProtocolBuffer &operator >>(bool &value);

	/**
	 * Reads an unsigned short (16 Bits)
	 */
	ProtocolBuffer &operator >>(unsigned short &value);

	/**
	 * Reads an array of integers (8 Bits * length + 32 Bits * value)
	 */
	ProtocolBuffer &operator >>(unsigned int **value);

	/**
	 * Reads an unsigned int (32 Bits)
	 */
	ProtocolBuffer &operator >>(unsigned int &value);

	/**
	 * Reads an unsigned long (64 Bits)
	 */
	ProtocolBuffer &operator >>(unsigned long &value);

	/**
	 * Reads a float (32 Bits)
	 */
	ProtocolBuffer &operator >>(float &value);

	/**
	 * Reads a double (64 Bits)
	 */
	ProtocolBuffer &operator >>(double &value);

	/**
	 * Reads an UTF-16 String
	 */
	ProtocolBuffer &operator >>(std::string &value);
private:
	boost::asio::streambuf *output;
	boost::asio::ip::tcp::socket *socket;
};

#endif // _PROTOCOL_BUFFER_HPP_
