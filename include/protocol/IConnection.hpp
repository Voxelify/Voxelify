/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _ICONNECTION_HPP_
#define _ICONNECTION_HPP_

#include <boost/asio/ip/address.hpp>
#include "IProtocol.hpp"

/**
 * The states of the connection
 */
enum ConnectionState {
    /**
     * The connection is connecting
     */
    CONNECTING = 0,
    /**
     * The connection is waiting for the exchange message
     */
    EXCHANGE_KEY,
    /**
     * The connection has received the login message
     */
    LOGGED,
    /**
     * The connection is disconnected
     */
    DISCONNECTED
};

/**
 * Encapsulate a single connection within the network.
 */
class IConnection
{
public:
	/**
	 * Gets the protocol
	 */
	virtual IProtocol &getProtocol() const = 0;

	/**
	 * Gets the current state. {@see ConnectionState}
	 */
	virtual ConnectionState getState() = 0;

	/**
	 * Sets the current state
	 *
	 * @param state the new state of the connection
	 */
	virtual void setState(ConnectionState state) = 0;

	/**
	 * Gets the address of where the connection is binded
	 */
	virtual boost::asio::ip::address &getAddress() const = 0;

	/**
	 * Sends a message
	 *
	 * @param message the message to send
	 */
	virtual void send(IMessage &message) = 0;

	/**
	 * Disconnect the connection with the specified reason.
	 *
	 * @param reason the reason why has been disconnected
	 */
	virtual void disconnect(std::string &reason) = 0;
};

#endif // _ICONNECTION_HPP_
