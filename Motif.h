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
#include "cocos2d.h"

class IMotif
{
public: 
	virtual void Run() = 0;
	virtual void TurnOffAllEmitters() = 0;
	virtual void TurnOnAllEmitters() = 0;
	virtual void SetPosition(cocos2d::Vec2 Position) = 0;

protected: 


	virtual void Update() = 0;
	virtual void Destroy() = 0;
};

class Motif : IMotif
{
public:
	Motif()
	:	RefreshRate(cocos2d::Director::getInstance()->getDeltaTime())
	{}

	virtual void Run() override;
	virtual void Destroy() override;

	~Motif();

protected:
	float RefreshRate;

	virtual void Update() override;
};