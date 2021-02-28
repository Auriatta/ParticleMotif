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
