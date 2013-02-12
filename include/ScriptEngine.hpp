/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _SCRIPT_ENGINE_HPP_
#define _SCRIPT_ENGINE_HPP_

extern "C"
{
#include "lua.h"
}
#include <luabind/luabind.hpp>

/**
 * Class to manage what class is registered as binded
 */
class ScriptEngine
{
public:
	/**
	 * Register the binding of the current class
	 */
	static void registerBinding(lua_State* state);
};

void
#endif // _SCRIPT_ENGINE_HPP_
