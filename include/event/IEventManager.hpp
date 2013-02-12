/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _IEVENT_MANAGER_HPP_
#define _IEVENT_MANAGER_HPP_

#include "IEvent.hpp"
#include "IEventListener.hpp"
#include "Priority.hpp"
#include <plugin/IPlugin.hpp">
#include <boost/function.hpp>

/**
* The event manager
*/
class IEventManager
{
public:
	/**
	* Calls an event
	*
	* @param event the event to call
	* @return the event data recieved though all callbacks
	*/
	virtual IEvent* callEvent(IEvent& event) const = 0;

	/**
	* Calls a delayed event, this event is not called in the main thread
	*
	* @param event the event to call
	*/
	virtual void callDelayedEvent(IEvent& event) = 0;

	/**
	* Register a listener
	*
	* @param owner the owner of the listener
	* @param listener the listener that contains many callbacks
	*/
	virtual void registerCallbacks(IPlugin& owner, IEventListener& listener) = 0;

	/**
	* Register a single callback
	*
	* @param owner the owner of the callbacks
	* @param function the function callback with the body "void onEvent(IEvent&)"
	* @param priority priority of the callback
	* @param id the event type uuid
	*/
	virtual void registerCallback(IPlugin& owner,  boost::function<void, IEvent&> function, Priority priority,  EventID id) = 0;

	/**
	* Unregister a single callback
	*
	* @param function to function callback
	*/
	virtual void unregisterCallback(IPlugin& owner, boost::function<void, IEvent>&> function) = 0;

	/**
	* Unregister all callbacks registered by a plugin
	*
	* @param owner the owner of the callbacks
	*/
	virtual void unregisterCallbacks(IPlugin& owner) = 0;
};

#endif // _IEVENT_MANAGER_HPP_
