/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */

#include <ScriptEngine.hpp>

using namespace luabind;

static void ScriptEngine::registerBinding(lua_State* state)
{
	// Module (Plugin)
	module(state)
	[
	    // plugin/PluginDescription.hpp
	    enum_<PluginDescription::Platform>("Platform")
	    [
	        value("SERVER", PluginDescription::Platform::SERVER),
	        value("CLIENT", PluginDescription::Platform::CLIENT),
	        value("BOTH", PluginDescription::Platform::BOTH)
	    ]
	    enum_<PluginDescription::Type>("Type")
	    [
	        value("LUA_SCRIPT", PluginDescription::Type::LUA_SCRIPT),
	        value("NATIVE", PluginDescription::Type::NATIVE)
	    ]
	    enum_<PluginDescription::LoadOrder>("LoadOrder")
	    [
	        value("INIT_STAGE", PluginDescription::LoadOrder::INIT_STAGE),
	        value("LOAD_STAGE",PluginDescription::LoadOrder::LOAD_STAGE)
	    ]
	    class_<PluginDescription>("PluginDescription")

	    // plugin/IPlugin.hpp
	    class_<IPlugin>("IPlugin")
	    .def("getInformation", &IPlugin::getInformation)
	    .def("isEnabled", &IPlugin::isEnabled)
	    .def("getDirectory", &IPlugin::getDirectory)
	    .def("getName", &IPlugin::getName)

	    // plugin/CPlugin.hpp, plugin/CPluginLua.hpp
	    class_<CPlugin, IPlugin>("CPlugin")
	    class_<CPluginLua, CPlugin>("CPluginLua")

	    // plugin/IPluginManager.hpp
	    class_<IPluginManager>("IPluginManager")
	    .def("getPlugin", &IPluginManager::getPlugin)
	    .def("getPlugins", &IPluginManager::getPlugins)
	];

	// Module (Protocol)
	module(state)
	[

	];
	//TODO: Add all bindings of the engine here.
}
