/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _CEVENT_MANAGER_HPP_
#define _CEVENT_MANAGER_HPP_

#include <event/IEventManager.hpp>
#include <boost/thread/recursive_mutex.hpp>

/**
 * Encapsulate the data that holds a handler
 */
typedef boost::tuple<EventID, boost::function<void, IEvent&>, Priority> HandlerType;

/**
* Default implementation of {@see IEventManager}
*/
class CEventManager : public IEventManager
{
public:
	/**
	 * Destructor of the event manager
	 */
	~CEventManager();

	/**
	 * {@inheritDoc}
	 */
	IEvent* callEvent(IEvent& event) const;

	/**
	 * {@inheritDoc}
	 */
	void callDelayedEvent(IEvent& event);

	/**
	 * {@inheritDoc}
	 */
	void registerCallbacks(IPlugin& owner, IEventListener& listener);

	/**
	 * {@inheritDoc}
	 */
	void registerCallback(IPlugin& owner,  boost::function<void, IEvent&> function, Priority priority,  EventID id);

	/**
	 * {@inheritDoc}
	 */
	void unregisterCallback(IPlugin& owner, boost::function<void, IEvent>&> function);

	/**
	 * {@inheritDoc}
	 */
	void unregisterCallbacks(IPlugin& owner);
private:
	boost::unordered_map<std::string, boost::list<HandlerType> > handlers;
	boost::recursive_mutex mutex;
};

#endif // _CEVENT_MANAGER_HPP_
