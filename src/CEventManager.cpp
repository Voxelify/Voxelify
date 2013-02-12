/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */

#include "CEventManager.hpp"

CEventManager::~CEventManager()
{

}

IEvent* CEventManager::callEvent(IEvent& event) const
{

}

void CEventManager::callDelayedEvent(IEvent& event)
{

}

void CEventManager::registerCallbacks(IEventListener& listener, IPlugin& owner)
{
	listener.onRegistration(this, owner);
}

void CEventManager::registerCallback(IPlugin& owner,  boost::function<void, IEvent&> function, Priority priority,  EventID id)
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex);
}

void CEventManager::unregisterCallback(IPlugin& owner, boost::function<void, IEvent>&> function)
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex);
}

void CEventManager::unregisterCallbacks(IPlugin& owner)
{

}
