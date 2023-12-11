

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
