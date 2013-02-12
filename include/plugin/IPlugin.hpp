/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _IPLUGIN_HPP_
#define _IPLUGIN_HPP_

#include "PluginDescription.hpp"
#include <boost/thread/recursive_mutex.hpp>
#include <boost/filesystem/path.hpp>

/**
 * Encapsulate the base class for any plugin.
 */
class IPlugin
{
public:
	/**
	 * Called when the plugin has been enabled
	 */
	virtual void onEnable() = 0;

	/**
	 * Called when the plugin has been disabled
	 */
	virtual void onDisable() = 0;

	/**
	 * Called one time when the plugin has been loaded for the first time
	 */
	virtual void onLoad() = 0;

	/**
	 * Called when the plugin has been reloaded
	 */
	virtual void onReload() = 0;

	/**
	 * Gets the information of the current plugin, that contains lots of
	 * useful information and data
	 */
	virtual PluginDescription &getDescription() = 0;

	/**
	 * Gets if the plugin is enabled
	 */
	virtual bool isEnabled() = 0;

	/**
	 * Sets if the plugin is enabled or not
	 *
	 * @param isEnabled TRUE or FALSE
	 */
	virtual void setEnabled(bool isEnabled) = 0;

	/**
	 * Gets the working directory of the plugin
	 */
	virtual boost::filesystem::path &getDirectory() = 0;

	/**
	 * Gets the critical section of this lua plugin
	 */
	virtual boost::recursive_mutex& getMutex() = 0;
	/**
	 * Gets the name of the plugin
	 */
	virtual std::string& getName() const = 0;
};

#endif // _IPLUGIN_HPP_
