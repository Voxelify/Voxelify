/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _PLUGIN_DISABLE_EVENT_HPP_
#define _PLUGIN_DISABLE_EVENT_HPP_

#include <event/IEvent.hpp>
#include <plugin/IPlugin.hpp>

/**
 * Define the event when a plugin has been disabled
 */
class PluginDisableEvent : public IEvent
{
public:
	IMPLEMENT_EVENT(PluginDisableEvent)

	/**
	 * Constructor of the event
	 *
	 * @param plugin the plugin event
	 */
	PluginDisableEvent(IPlugin& plugin) {
		this->plugin = plugin;
	}

	/**
	 * Gets the plugin of the event
	 */
	IPlugin& getPlugin() const {
		return plugin;
	}

	/**
	 * {@inheritDoc}
	 */
	std::string& getName() const {
		return "PluginDisableEvent";
	}
private:
	IPlugin plugin;
}

#endif // _PLUGIN_DISABLE_EVENT_HPP_
