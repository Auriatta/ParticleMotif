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

#include "MotifExpositionMenager.h"

/*Motif Type*/
template<typename T>
class MotifExpositionRandom : public MotifExposition<T>, public IMotifExpositionMultiTick
{
public:
	MotifExpositionRandom(MotifExposition<T>::MotifExposition BaseData,
		IMotifExpositionMultiTick::IMotifExpositionMultiTick Ticks)
		: MotifExposition<T>(BaseData),
		IMotifExpositionMultiTick(Ticks)
	{}
	
	virtual void Run() override();
	virtual void Update() override();

protected:

	virtual bool CreateOne() override();

	virtual void SwitchToTickIntervalShow();
	virtual void SwitchToTickIntervalHide();


	cocos2d::Vec2 GetRandomPosition(cocos2d::Vec4& BorderBox);
};


template<class T>
inline bool MotifExpositionRandom<T>::CreateOne()
{
	if (MotifBuffer.size() >= MotifAmount)
		return false;
	else
	{
		MotifBuffer.push_front(new T());
		MotifBuffer.front()->SetPosition(GetRandomPosition());
		MotifBuffer.front()->Run();
	}
	return true;
}


template<class T>
inline void MotifExpositionRandom<T>::Update()
{
	if (MotifBuffer.size() >= MotifAmount)
	{
		if (MotifExposition<T>::GoalSwitch == 0)
		{
			SwitchToTickIntervalHide(); // do once
		}
		else
			SwitchToTickIntervalShow(); // do once
	}

	MotifExposition<T>::Update();
}

template<class T>
inline void MotifExpositionRandom<T>::Run()				// refactoring!
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(
		cocos2d::ccSchedulerFunc(std::bind(&MotifExpositionRandom<T>::Update, this)),
		this, MotifExposition<T>::TickInterval, 0, MotifExposition<T>::ScheduleName);
}

template<class T>
inline void MotifExpositionRandom<T>::SwitchToTickIntervalShow()		// refactoring!
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(
		cocos2d::ccSchedulerFunc(std::bind(&MotifExpositionRandom<T>::Update, this)),
		this, IMotifExpositionMultiTick::TickIntervalShow, 0, MotifExposition<T>::ScheduleName);
}

template<class T>
inline void MotifExpositionRandom<T>::SwitchToTickIntervalHide()		// refactoring!
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(
		cocos2d::ccSchedulerFunc(std::bind(&MotifExpositionRandom<T>::Update, this)),
		this, IMotifExpositionMultiTick::TickIntervalHide, 0, MotifExposition<T>::ScheduleName);
}


template<class T>
inline cocos2d::Vec2 MotifExpositionRandom<T>::GetRandomPosition(cocos2d::Vec4& BorderBox)
{
	return cocos2d::Vec2(
		cocos2d::RandomHelper::random_int<int>(BorderBox.x, BorderBox.w),
		cocos2d::RandomHelper::random_int<int>(BorderBox.y, BorderBox.z));
}