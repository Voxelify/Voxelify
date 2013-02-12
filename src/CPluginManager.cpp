/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */

#include "CPluginManager.hpp"

CPluginManager::CPluginManager(std::string& folder)
{
	this->folder = folder;
}

CPluginManager::~CPluginManager()
{
	disablePlugins();
	unregisterPlugins();
}

std::string& CPluginManager::getFolder() const
{
	return folder;
}

bool CPluginManager::registerPlugin(std::string &name)
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex);
	//TODO: Register plugin
}

void CPluginManager::unregisterPlugin(IPlugin &plugin)
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex);
	//TODO: Unregister plugin
}

IPlugin *CPluginManager::getPlugin(std::string &name)
{
	BOOST_FOREACH(boost::unordered_map<std::string, IPlugin*>::value_type it, pluginMap) {
		if( (it.second != nullptr) && (it.second.getName().compare(name) == 0))
			return it.second;
	}
	return nullptr;
}

boost::unordered_map<std::string, IPlugin *> &CPluginManager::getPlugins() const
{
	return pluginMap;
}

void CPluginManager::enablePlugin(IPlugin &plugin)
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex);
	//TODO: Enable plugin
	// TODO: Call EnablePluginEvent
}

void CPluginManager::disablePlugin(IPlugin &plugin)
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex);
	if( !plugin.isEnabled() )
		return;
	// TODO: Remove everything (Commands, Listeners)
	// TODO: Call DisablePluginEvent
	plugin.onDisable();
	plugin.setEnabled(false);
}

void CPluginManager::disablePlugins()
{
	BOOST_FOREACH(boost::unordered_map<std::string, IPlugin*>::value_type it, pluginMap) {
		disablePlugin(it.second);
	}
}

void CPluginManager::unregisterPlugins()
{
	while(pluginMap.size() > 0)
		unregisterPlugin(pluginMap.begin()->second->getName());
}
