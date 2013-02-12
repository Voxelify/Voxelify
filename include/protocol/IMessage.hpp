/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _IMESSAGE_HPP_
#define _IMESSAGE_HPP_

/**
 * Encapsulate a packet that is transmitted though a socket.
 */
class IMessage
{
public:
	/**
	 * Gets the ID of the message
	 */
	virtual unsigned int getId() = 0;
};

#endif // _IMESSAGE_HPP_
