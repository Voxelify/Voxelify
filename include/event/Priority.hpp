/*
 * Copyright 2013 Voxelify, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _PRIORITY_HPP_
#define _PRIORITY_HPP_

/**
 * Define the priority of an even't callback.
 */
enum Priority {
    /**
    	* Lowest priority
    	*/
    LOWEST
    /**
     * Low priority
     */
    LOW
    /**
     * Normal priority
     */
    NORMAL
    /**
     * High priority
     */
    HIGH
    /**
     * Highest priority
     */
    HIGHEST
    /**
     * Monitor priority
     */
    MONITOR
};

#endif // _PRIORITY_HPP_
