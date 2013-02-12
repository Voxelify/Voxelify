/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _IEVENT_LISTENER_HPP_
#define _IEVENT_LISTENER_HPP_

/**
 * Define the entry point of the event listener
 */
#define EVENT_BINDING_START() \
	void onRegistration(IEventManager& eventManager,  IPlugin& owner) { \
		 
/**
  * Bind a function to the listener
  */
#define EVENT_BIND(Function, Priority, EventType) \
	eventManager.registerCallback(owner, Function, Priority, EventType::getStaticUniqueID()); \
	 
/**
  * End the binding process
  */
#define EVENT_BINDING_END() \
	} \
	 
/**
 * Define the base class for any {@see IEvent}'s listener
 */
class IEventListener
{
public:
	/**
	 * This function is called to register every event in the listener
	 *
	 * @param eventManager the manager of the events.
	 * @param owner owner of this listener
	 */
	*/
	virtual void onRegistration(IEventManager& eventManager, IPlugin& owner);
};

#endif // _IEVENT_LISTENER_HPP_
