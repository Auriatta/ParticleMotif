#pragma once
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

	~IMotifExposition() = default;
protected:
	virtual bool CreateOne() = 0;
	virtual bool Show() = 0;
	virtual bool Hide() = 0;

	virtual void DestroyAll() = 0;

	int MotifAmount = 0;
	std::list<T*> MotifBuffer;
	typename std::list<T*>::iterator MotifBuffer_it;
};

template<typename T>
class MotifExposition : IMotifExposition<T>
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

	virtual void Run();
	virtual void Update();

	~MotifExposition()
	{
		// clear the mess
	}

protected:
	float TickCounter;
	bool GoalSwitch;
	float DelayToShow;
	float DelayToHide;
	float TickInterval;
	std::string ScheduleName;

	virtual bool CreateOne();
	virtual bool Show();
	virtual bool Hide();


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
		float TickIntervalHide = 0.2, float TickIntervalInit = 0.4)
	{}

protected:
	virtual void SwitchToTickIntervalShow() = 0;
	virtual void SwitchToTickIntervalHide() = 0;
};


template<typename T>
class MotifExpositionRandom : MotifExposition<T>, IMotifExpositionMultiTick
{
public:
	MotifExpositionRandom()
		: MotifExposition<T>(),
		IMotifExpositionMultiTick()
	{}


	virtual void Update() override();

protected:

	virtual bool CreateOne() override();
	virtual void SwitchToTickIntervalShow();
	virtual void SwitchToTickIntervalHide();


	cocos2d::Vec2 GetRandomPosition();
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