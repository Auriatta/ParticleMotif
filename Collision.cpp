#include "Collision.h"

bool Collision::isStuckOnBarrier(cocos2d::Point _position)
{
	cocos2d::Rect barrier;
	barrier.origin.x = BORDER_X_ORIGIN;
	barrier.origin.y = BORDER_Y_ORIGIN;
	barrier.size.width = BORDER_WIDTH;
	barrier.size.height = BORDER_HEIGHT;

	if (!barrier.containsPoint(_position))
		return true;

	return false;
}
