/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */

#include "CPlugin.hpp"

void CPlugin::(boost::filesystem::path& folder, PluginDescription& description, IPluginManager& pluginManager)
{
	this->folder = folder;
	this->description = description;
	this->pluginManager = pluginManager;
}

virtual void CPlugin::~CPlugin()
{
}

void CPlugin::onEnable()
{
}

void CPlugin::onDisable()
{
}

void CPlugin::onLoad()
{
}

void CPlugin::onReload()
{
}

PluginDescription &CPlugin::getDescription()
{
	return description;
}

bool CPlugin::isEnabled()
{
	return enabledFlag;
}

void CPlugin::setEnabled(bool isEnabled)
{
	enabledFlag = isEnabled;
}

boost::filesystem::path &CPlugin::getDirectory()
{
	return folder;
}

boost::recursive_mutex& CPlugin::getMutex()
{
	return mutex;
}

IPluginManager* CPlugin::getPluginManager() const
{
	return pluginManager;
}

std::string& CPlugin::getName() const
{
	return description.getName();
}
