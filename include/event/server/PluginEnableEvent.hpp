/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _PLUGIN_ENABLE_EVENT_HPP_
#define _PLUGIN_ENABLE_EVENT_HPP_

#include <event/IEvent.hpp>
#include <plugin/IPlugin.hpp>

/**
 * Define the event when a plugin has been enabled
 */
class PluginEnableEvent : public IEvent
{
public:
	IMPLEMENT_EVENT(PluginEnableEvent)

	/**
	 * Constructor of the event
	 *
	 * @param plugin the plugin event
	 */
	PluginEnableEvent(IPlugin& plugin) {
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
		return "PluginEnableEvent";
	}
private:
	IPlugin plugin;
}

#endif // _PLUGIN_ENABLE_EVENT_HPP_
