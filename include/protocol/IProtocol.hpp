/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _IPROTOCOL_HPP_
#define _IPROTOCOL_HPP_

#include "IMessage.hpp"
#include "ProtocolBuffer.hpp"

/**
 * Encapsulate the protocol decoder, encoder and handler for every packet
 * in the game of this protocol.
 */
class IProtocol
{
public:
	/**
	 * Gets the name of the protocol
	 */
	virtual std::string &getName() const = 0;

	/**
	 * Gets the lenght of the header
	 */
	virtual unsigned int getHeaderLenght() const = 0;

	/**
	 * Reads a message that was sended by the remote connection
	 *
	 * @param in the buffer to read the message data
	 * @param id the id of the message
	 */
	virtual IMessage *readMessage(ProtocolBuffer &in, unsigned int id) = 0;

	/**
	 * Writes a message to the remote connection
	 *
	 * @param out the buffer to store the message data
	 * @param message the message to send
	 */
	virtual void writeMessage(ProtocolBuffer &out, IMessage &message) = 0;
};

#endif // _IPROTOCOL_HPP_
