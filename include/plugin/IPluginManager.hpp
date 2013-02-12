/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _IPLUGIN_MANAGER_HPP_
#define _IPLUGIN_MANAGER_HPP_

#include "IPlugin.hpp"
#include <boost/unordered_map.hpp>

/**
 * Encapsulate the manager for all {@see IPlugin}'s
*/
class IPluginManager
{
public:
	/**
	 * Gets the base folder of the plugins
	 */
	virtual boost::filesystem::path& getFolder() const = 0;

	/**
	 * Register a new plugin into the system
	 *
	 * @param name the name of the plugin
	 * @return if the plugin was succesfull registered
	 */
	virtual bool registerPlugin(std::string &name) = 0;

	/**
	 * Unregister a plugin from the system
	 *
	 * @param plugin the plugin
	 */
	virtual void unregisterPlugin(IPlugin &plugin) = 0;

	/**
	 * Gets a plugin registered from the current
	 * plugin's storage
	 *
	 * @param the name of the plugin
	 * @return the plugin with that name, NULL if doesn't exist
	 */
	virtual IPlugin *getPlugin(std::string &name) = 0;

	/**
	 * Gets all plugins registered into the manager
	 */
	virtual boost::unordered_map<std::string, IPlugin *> &getPlugins() const = 0;

	/**
	 * Enable a plugin
	 *
	 * @param plugin the plugin to enable
	 */
	virtual void enablePlugin(IPlugin &plugin) = 0;

	/**
	 * Disable a plugin
	 *
	 * @param plugin the plugin to disable
	 */
	virtual void disablePlugin(IPlugin &plugin) = 0;

	/**
	 * Disable all plugins from the manager
	 */
	virtual void disablePlugins() = 0;

	/**
	 * Unregister all plugins from the manager
	 */
	virtual void unregisterPlugins() = 0;
};

#endif // _IPLUGIN_MANAGER_HPP_
