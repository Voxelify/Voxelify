/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _EVENT_HPP_
#define _EVENT_HPP_

typedef unsigned char EventID;

/**
 * Define a way to make every event unique
 */
#define IMPLEMENT_EVENT(Clazz) \
	static EventID* getStaticUniqueID() { \
		static EventID sUID = 0; \
		return (EventID)&sUID; \
	} \
	virtual EventID* getUniqueID() const  { \
		Clazz::getStaticUniqueID(); \
	} \
	 
/**
 * Define the base class for any event
 */
class IEvent
{
public:
	IMPLEMENT_EVENT(IEvent);
public:
	/**
	 * Gets the name of the event
	 */
	virtual std::string& getName() const {
		return "IEvent";
	}

	/**
	 * Gets if the event wasn't cancelled, this flag will stop propagation
	 */
	bool isCancelled() {
		return cancelled;
	}

	/**
	 * Sets the cancelled flag of the event
	 *
	 * @param cancel the new value
	 */
	void setCancelled(bool cancel) {
		cancelled = cancel;
	}
protected:
	bool cancelled;
}

#endif // _EVENT_HPP_
