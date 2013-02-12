/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _IMESSAGE_HANDLER_HPP_
#define _IMESSAGE_HANDLER_HPP_

#include "IMessage.hpp"
#include "IConnection.hpp"

/**
 * Encapsulate the {@see IMessage}'s handler.
 */
class IMessageHandler
{
public:
	/**
	 * Handle the message in the client side
	 *
	 * @param connection the connection of the platform
	 * @param message the message to handle
	 */
	virtual void handleClient(IConnection &connection, IMessage &message) = 0;
	/**
	 * Handle the message in the client side
	 *
	 * @param connection the connection of the platform
	 * @param message the message to handle
	 */
	virtual void handleServer(IConnection &connection, IMessage &message) = 0;
};

#endif // _IMESSAGE_HANDLER_HPP_
