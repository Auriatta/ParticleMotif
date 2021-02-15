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
