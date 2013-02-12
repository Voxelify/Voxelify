/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _IMESSAGE_CODEC_HPP_
#define _IMESSAGE_CODEC_HPP_

#include "IMessage.hpp"
#include "ProtocolBuffer.hpp"

/**
 * Encapsulate a codec for a {@see IMessage}. Contains the
 * read and write function for it.
 */
class IMessageCodec
{
public:
	/**
	 * Store the message into an output stream
	 *
	 * @param message the message to write into
	 * @param out the output stream
	 */
	virtual void write(IMessage &message, ProtocolBuffer &out) = 0;

	/**
	 * Gets the message from an input stream
	 *
	 * @param in the input stream
	 * @return the message read from the buffer
	 */
	virtual IMessage *read(ProtocolBuffer &in) = 0;
};

#endif // _IMESSAGE_CODEC_HPP_
