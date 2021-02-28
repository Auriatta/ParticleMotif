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

#pragma once
#include "PreDefines.h"
#include "Collision.h"
#include "cocos2d.h"


class AI
{
public:
	AI()
	{}

	virtual void update()=0;

	cocos2d::Point getPosition() { return _position; };

	virtual void resetDirection() = 0;

	~AI()=default;

protected:
	void setPosition(cocos2d::Point _position) { this->_position = _position; };

	void setDirection(cocos2d::Point _direction) { this->_direction = _direction; };
	cocos2d::Point getDirection() { return _direction; };

private:
	cocos2d::Point _position;
	cocos2d::Point _direction;
};


/*
Bahavior:
1) Run foward
2) If stuck on barrier: turn around
3) Back to 1)
*/
class AI_Basic
	: public AI
{
public:
	AI_Basic(cocos2d::Point _startPosition = cocos2d::Vec2(0,0),
		cocos2d::Point speed = cocos2d::Vec2(1, 1))
		: dirModifier(speed)
	{
		AI::setPosition(_startPosition);
		AI::setDirection(initDirection());
	}

	void update() override;
	void resetDirection() override;

	~AI_Basic() = default;

private:
	const cocos2d::Point dirModifier; // XY move length (per update) is modified by this value;


	cocos2d::Point initDirection();


	void setOpositeDirection();
	void updateDirection();
};
