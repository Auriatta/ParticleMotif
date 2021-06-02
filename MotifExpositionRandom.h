#pragma once

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

#include "MotifExpositionMultiTick.h"




template<class T_Motif>
class MotifExpositionRandom : public MotifExpositionMultiTick<T_Motif>
{
public:
	MotifExpositionRandom(
		MotifExposition<T_Motif> &Base, cocos2d::Vec4& SpawnArea,
		float TickIntervalShow = 0.2,
		float TickIntervalHide = 0.2)
		:
		MotifExpositionMultiTick<T_Motif>(Base, TickIntervalShow, TickIntervalHide),
		SpawnArea(SpawnArea)
	{}
	
	
protected:	
	virtual void CreateOne() override;
	

	cocos2d::Vec2 GetRandomPosition(cocos2d::Vec4& BorderBox);

	cocos2d::Vec4 SpawnArea;
};


template<class T_Motif>
inline void MotifExpositionRandom<T_Motif>::CreateOne()
{
	MotifBuffer.push_front(new T_Motif());
	MotifBuffer.front()->SetPosition(GetRandomPosition(SpawnArea));
	MotifBuffer.front()->Init();
	MotifBuffer.front()->Run();
	
}



template<class T_Motif>
inline cocos2d::Vec2 MotifExpositionRandom<T_Motif>::GetRandomPosition(cocos2d::Vec4& BorderBox)
{
	return cocos2d::Vec2(
		cocos2d::RandomHelper::random_int<int>(BorderBox.x, BorderBox.w),
		cocos2d::RandomHelper::random_int<int>(BorderBox.y, BorderBox.z));
}