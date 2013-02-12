/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _CPLUGIN_MANAGER_HPP_
#define _CPLUGIN_MANAGER_HPP_

#include <plugin/IPluginManager.hpp>

/**
 * Common implementation of {@see IPluginManager}
 */
class CPluginManager : public IPluginManager
{
public:
	/**
	 * Constructor of the plugin manager
	 *
	 * @param folder the folder where all plugins are at
	 */
	CPluginManager(std::string& folder);

	/**
	 * Destructor of the plugin manager
	 */
	~CPluginManager();

	/**
	 * {@inheritDoc}
	 */
	boost::filesystem::path& getFolder() const;

	/**
	 * {@inheritDoc}
	 */
	bool registerPlugin(std::string &name);

	/**
	 * {@inheritDoc}
	 */
	void unregisterPlugin(IPlugin &plugin);

	/**
	 * {@inheritDoc}
	 */
	IPlugin *getPlugin(std::string &name);

	/**
	 * {@inheritDoc}
	 */
	boost::unordered_map<std::string, IPlugin *> &getPlugins() const;

	/**
	 * {@inheritDoc}
	 */
	void enablePlugin(IPlugin &plugin);

	/**
	 * {@inheritDoc}
	 */
	void disablePlugin(IPlugin &plugin);

	/**
	 * {@inheritDoc}
	 */
	void disablePlugins();

	/**
	 * {@inheritDoc}
	 */
	void unregisterPlugins();
private:
	boost::filesystem::path folder;
	boost::unordered_map<std::string, IPlugin*> pluginMap;
	boost::recursive_mutex mutex;
}

#endif // _CPLUGIN_MANAGER_HPP_
