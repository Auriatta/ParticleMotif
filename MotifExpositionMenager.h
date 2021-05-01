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

#include "PreDefines.h"
#include"cocos2d.h"
#include <string>

template<typename T>
class IMotifExposition
{
public:
	IMotifExposition()
	{};
	virtual void Run() = 0;
	virtual void Update() = 0;
	std::list<T*>* GetMotifList() { return &MotifBuffer;  };

protected:
	virtual bool CreateOne() = 0;
	virtual bool Show() = 0;
	virtual bool Hide() = 0;


	int MotifAmount = 0;
	std::list<T*> MotifBuffer;
	typename std::list<T*>::iterator MotifBuffer_it;
};

template<typename T>
class MotifExposition : public IMotifExposition<T>
{
public:
	MotifExposition(float DelayToShow, float DelayToHide,
		int MotifAmount = 1, float TickInterval = 0.2)
		: TickInterval(TickInterval), DelayToShow(DelayToShow), DelayToHide(DelayToHide),
		ScheduleName("MainUpdate"), TickCounter(0)
	{
		IMotifExposition<T>::MotifAmount = MotifAmount;
		IMotifExposition<T>::MotifBuffer_it = MotifBuffer.begin();
	}

	virtual void Run() override;
	virtual void Update() override;

	

protected:
	float TickCounter;
	bool GoalSwitch;
	float DelayToShow;
	float DelayToHide;
	float TickInterval;
	std::string ScheduleName;

	virtual bool CreateOne() override;
	virtual bool Show() override;
	virtual bool Hide() override;


};


template<class T>
inline void MotifExposition<T>::Run()
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(
		cocos2d::ccSchedulerFunc(std::bind(&MotifExposition<T>::Update, this)),
		this, TickInterval, 0, ScheduleName);
}

template<class T>
inline void MotifExposition<T>::Update()
{
	if (!CreateOne())
	{
		TickCounter += TickInterval;

		if (GoalSwitch && TickCounter > DelayToHide)
		{
			if (!Hide())
			{
				TickCounter = 0;
				GoalSwitch = 0;
				return;
			}
		}

		if (!GoalSwitch && TickCounter > DelayToShow)
		{
			if (!Show())
			{
				TickCounter = 0;
				GoalSwitch = 1;
				return;
			}
		}
	}
}

template<class T>
inline bool MotifExposition<T>::CreateOne()
{
	if (MotifBuffer.size() >= MotifAmount)
		return false;
	else
	{
		MotifBuffer.push_front(new T());
		MotifBuffer.front()->Run();
	}
	return true;
}

template<class T>
inline bool MotifExposition<T>::Show()
{
	if (MotifBuffer_it == MotifBuffer.end())
		return false;
	MotifBuffer_it++;
	(*MotifBuffer_it)->TurnOnAllEmitters();
	return true;
}

template<class T>
inline bool MotifExposition<T>::Hide()
{
	if (MotifBuffer_it == MotifBuffer.begin())
		return false;
	MotifBuffer_it--;
	(*MotifBuffer_it)->TurnOffAllEmitters();
	return true;
}




class IMotifExpositionMultiTick
{
	/*
	* @Param TickIntervalShow - Refresh rate for single motif at showing status
	* @Param TickIntervalHide - Refresh rate for single motif at hiding status
	* @param TickIntervalInit - Refresh rate for single motif creation
	*/
public:
	IMotifExpositionMultiTick(float TickIntervalShow = 0.2,
		float TickIntervalHide = 0.2)
		: TickIntervalShow(TickIntervalShow), TickIntervalHide(TickIntervalHide)
	{}

protected:
	virtual void SwitchToTickIntervalShow() = 0;
	virtual void SwitchToTickIntervalHide() = 0;
	float TickIntervalShow;
	float TickIntervalHide;
	
};


