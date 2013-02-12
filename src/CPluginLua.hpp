/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _CPLUGIN_LUA_HPP_
#define _CPLUGIN_LUA_HPP_

#include "CPlugin.hpp"
#include <ScriptEngine.hpp>

/**
 * Common implementation for a {@see CPlugin} that use LUA as the interpreter
 */
class CPluginLua : public CPlugin
{
public:
	/**
	 * Constructor of the plugin	
	 *
	 * @param folder the data folder of the plugin
	 * @param description plugin's description"
	 * @param pluginManager the manager of this plugin
	 */
	CPluginLua(boost::filesystem::path& folder, PluginDescription& description, IPluginManager& pluginManager);

	/**
	 * Destructor of the plugin
	 */
	~CPluginLua();

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
	 * Gets the lua state of this plugin.
	 */
	lua_state* getState() const;
private:
	/**
	 * Add a scripting file into the state
	 *
	 * @param path the path of the scripting file
	 * @return TRUE or FALSE
	 */
	bool addScriptFile(boost::filesystem::path& path);

protected:
	lua_State* state;
};

#endif // _CPLUGIN_LUA_HPP_
