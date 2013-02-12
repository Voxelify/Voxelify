/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _CPLUGIN_HPP_
#define _CPLUGIN_HPP_

#include <plugin/IPluginManager.hpp>

/**
 * Common implementation of {@see IPlugin}
 */
class CPlugin : public IPlugin
{
public:
	/**
	 * Constructor of the plugin
	 *
	 * @param folder the data folder of the plugin
	 * @param description plugin's description
	 * @param pluginManager the manager of this plugin
	 */
	CPlugin(boost::filesystem::path& folder, PluginDescription& description, IPluginManager& pluginManager);

	/**
	 * Destructor of the plugin
	 */
	virtual ~CPlugin();

	/**
	 * {@inheritDoc}
	 */
	void onEnable();

	/**
	 * {@inheritDoc}
	 */
	void onDisable();

	/**
	 * {@inheritDoc}
	 */
	void onLoad();

	/**
	 * {@inheritDoc}
	 */
	void onReload();

	/**
	 * {@inheritDoc}
	 */
	PluginDescription &getDescription();

	/**
	 * {@inheritDoc}
	 */
	bool isEnabled();

	/**
	 * {@inheritDoc}
	 */
	void setEnabled(bool isEnabled);

	/**
	 * {@inheritDoc}
	 */
	boost::filesystem::path &getDirectory();

	/**
	 * {@inheritDoc}
	 */
	boost::recursive_mutex& getMutex();

	/**
	 * {@inheritDoc}
	 */
	IPluginManager* getPluginManager() const;

	/**
	 * {@inheritDoc}
	 */
	std::string& getName() const;
protected:
	boost::filesystem::path folder;
	bool enabledFlag;
	PluginDescription description;
	boost::recursive_mutex mutex;
	IPluginManager* pluginManager;
};

#endif // _CPLUGIN_HPP_
