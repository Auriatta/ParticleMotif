#include "AI.h"

cocos2d::Point AI_Basic::initPosition()
{
	const cocos2d::Point offset(50, 50);
	return cocos2d::Point(BORDER_X_ORIGIN+offset.x,
		BORDER_Y_ORIGIN+ offset.y);
}

cocos2d::Point AI_Basic::initDirection()
{
	return cocos2d::Point(
		Random::random_int<int>(0,1) ? dirModifier.x : -(dirModifier.x),
		Random::random_int<int>(0,1) ? dirModifier.y : -(dirModifier.y));
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
	if (Collision::isStuckOnBarrier(AI::getDirection()))
		setOpositeDirection();

	
	AI::setPosition(
		cocos2d::Point(
			AI::getPosition().x + AI::getDirection().x,
			AI::getPosition().y + AI::getDirection().y) );
}


void AI_Basic::update()
{
	updateDirection();
}

void AI_Basic::resetDirection()
{
	initDirection();
}
