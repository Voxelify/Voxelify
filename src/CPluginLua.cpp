/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */

#include "CPluginLua.hpp"
#include <boost/log/trivial.hpp>

CPluginLua::CPluginLua(boost::filesystem::path& folder, PluginDescription& description, IPluginManager& pluginManager)
	: CPlugin(folder, description, pluginManager)
{
	this->state = nullptr;
}

~CPluginLua::CPluginLua()
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex);
	if( state != nullptr )
		lua_close(state);
}

void CPluginLua::onEnable()
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex);
	if( state != nullptr)
		luabind::call_function<void>(state, "onEnable");
}

void CPluginLua::onDisable()
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex);
	if( state != nullptr)
		luabind::call_function<void>(state, "onDisable");
}

void CPluginLua::onLoad()
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex);
	if( state != nullptr ) {
		try {
			state = luaL_newstate();
		} catch(luabind::error& ex) {
			state = nullptr;
			BOOST_LOG_TRIVIAL(error) << "[" << getName() << "]: Cannot create Lua state";
			return;
		}
		luabind::open(state);
		ScriptEngine::registerBinding(state);
	}

	// Register our plugin instance
	luabind::globals(state) ["this"] = this;

	// Load every .lua file from {$PluginFolder}/{$PluginName}/scripts
	boost::filesystem::path directory(folder + "scripts");
	boost::filesystem::directory_iterator itEnd;

	if( boost::filesystem::exists(directory) && boost::filesystem::is_directory(directory) ) {
		lua_close(state);
		state = nullptr;
		BOOST_LOG_TRIVIAL(error) << "[" << getName()
		                         << "]: The script folder is invalid, remember to place all your lua files inside '/scripts'";
		return;
	}

	for( boost::filesystem::directory_iterator itDir(directory) ; itDir != itEnd ; ++itDir) {
		if (boost::filesystem::is_regular_file(itDir->status()) && !addScriptFile(iter->path) )
			return;
	}

	// Calls the onLoad function of the plugin
	luabind::call_function<void>(state,  "onLoad");
}

void CPluginLua::onReload()
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex);
	if( state != nullptr)
		luabind::call_function<void>(state, "onReload");
}

lua_state* CPluginLua::getState() const
{
	return state;
}

bool CPluginLua::addScriptFile(std::string& path)
{
	int ret = luaL_loadfile(state, path);
	if( report_errors(state, ret) ) {
		lua_close(state);
		state = nullptr;
		BOOST_LOG_TRIVIAL(error) << "[" << getName()
		                         << "]: The script file '" << path << "' has a compilation error";
		return false;
	}
	return true;
}
