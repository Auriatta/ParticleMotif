#pragma once
#include "PreDefines.h"
#include "cocos2d.h"

class Collision
{
public:
	Collision() 
	{}

	static bool isStuckOnBarrier(cocos2d::Point);
};