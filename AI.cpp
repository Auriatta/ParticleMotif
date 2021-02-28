/*
* Copyright (c) <2021> <Alex 'Auriatta' Ates>.
All rights reserved.

Redistribution and use in source and binary forms are permitted provided
that the above copyright notice and this paragraph are duplicated in all
such forms and that any documentation, advertising materials, and other
materials related to such distribution and use acknowledge that the software
was developed by the <Alex 'Auriatta' Ates>.
The name of the <Alex 'Auriatta' Ates> may not be used to endorse or promote
products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED ``AS IS'' AND
WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE.
* Contact me at Auriattadev.com
*/

#include "AI.h"



cocos2d::Point AI_Basic::initDirection()
{
	return cocos2d::Point(
		cocos2d::RandomHelper::random_int<int>(0,1) ? dirModifier.x : -(dirModifier.x),
		cocos2d::RandomHelper::random_int<int>(0,1) ? dirModifier.y : -(dirModifier.y));
}

void AI_Basic::setOpositeDirection()
{
	if (AI::getPosition().x < BORDER_X_ORIGIN)
		AI::setDirection(cocos2d::Point(dirModifier.x, AI::getDirection().y));
	if (AI::getPosition().x > BORDER_WIDTH)
		AI::setDirection(cocos2d::Point(-(dirModifier.x), AI::getDirection().y));

	if (AI::getPosition().y < BORDER_Y_ORIGIN)
		AI::setDirection(cocos2d::Point(AI::getDirection().x, dirModifier.y));
	if (AI::getPosition().y > BORDER_HEIGHT)
		AI::setDirection(cocos2d::Point(AI::getDirection().x, -(dirModifier.y)));
}

void AI_Basic::updateDirection()
{
	const cocos2d::Vec2 NewPosition = AI::getPosition() + AI::getDirection();
	if (Collision::isStuckOnBarrier(NewPosition))
		setOpositeDirection();

	
	AI::setPosition(NewPosition);
}


void AI_Basic::update()
{
	updateDirection();
}

void AI_Basic::resetDirection()
{
	initDirection();
}
