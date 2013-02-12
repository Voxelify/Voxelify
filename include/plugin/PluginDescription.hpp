/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _PLUGIN_DESCRIPTION_HPP_
#define _PLUGIN_DESCRIPTION_HPP_

#include <boost/container/vector.hpp>

/**
 * Contains the information of a single plugin, such as name,
 * when is loaded and the dependencies.
 */
class PluginDescription
{
	/**
	 * Define when is the plugin loaded
	 */
	enum LoadOrder {
	    /**
	     * Initialization stage is before the world has been generated.
	     */
	    INIT_STAGE,
	    /**
	     * Loading stage is after the world has been generated.
	     */
	    LOADING_STAGE
	};
	/**
	 * Encapsulate the execution type of the plugin
	 */
	enum Type {
	    /**
	     * The plugin is executed by a lua interpreter.
	     */
	    LUA_SCRIPT,
	    /**
	     * The plugin is executed by the os.
	     */
	    NATIVE
	};
	/**
	 * Define the available platform for the engine.
	 */
	enum Platform {
	    /**
	     * Server platform
	     */
	    SERVER = 0,
	    /**
	     * Client platform
	     */
	    CLIENT = 1,
	    /**
	     * Server and client platform
	     */
	    BOTH = 2
	};
public:

	/**
	 * Constructor of the configuration file
	 *
	 * @param name the plugin's name
	 * @param version the plugin's version
	 * @param depends the plugin's dependencies
	 * @param platform the plugin's platform
	 * @param order the plugin's order
	 * @param type the plugin's type
	 */
	PluginDescription(std::string &name, unsigned int version,  boost::container::vector<std::string> &depends,
	                  Platform platform, LoadOrder order, Type type) {
		this->name = name;
		this->version = version;
		this->platform = platform;
		this->order = order;
		this->type = type;
		this->depends = depends;
	}

	/**
	 * Gets the plugin's name
	 */
	inline std::string &getName() {
		return name;
	}

	/**
	 * Gets the plugin's version
	 */
	inline unsigned int getVersion() {
		return version;
	}

	/**
	 * Gets the plugin's platform
	 */
	inline Platform getPlatform() {
		return platform;
	}

	/**
	 * Gets the plugin's order
	 */
	inline LoadOrder getOrder() {
		return load;
	}

	/**
	 * Gets the plugin's dependencies
	 */
	inline boost::container::vector<std::string> &getDepends() {
		return depends;
	}

	/**
	 * Gets the plugin's type
	 */
	inline Type getType() {
		return type;
	}

protected:
	std::string name;
	unsigned int version;
	boost::container::vector<std::string> depends;
	Platform platform;
	LoadOrder order;
	Type type;
};

#endif // _PLUGIN_DESCRIPTION_HPP_
