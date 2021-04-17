#pragma once
#include "PreDefines.h"
#include"cocos2d.h"
#include <string>

template<typename T>
class SequencedShow
{
public:
	SequencedShow(std::list<T*>* MotifListRef,
		float ShowedDelay, float HiddenDelay,
		float MotifNumber = 1, float TickInterval = 0.2)
		: ShowedDelay(ShowedDelay), TickInterval(TickInterval),
		TickCounter(0), MotifNumber(MotifNumber), GoalSwitch(0),
		MotifListRef(MotifListRef), HiddenDelay(HiddenDelay)
	{}
		

	void SequencedShow<T>::Update(float delta);

	~SequencedShow() = default;
private:
	int MotifNumber;
	std::list<T*>* MotifListRef;
	float TickCounter;
	bool GoalSwitch;
	float ShowedDelay;
	float HiddenDelay;
	float TickInterval;
	
	bool AddOne();

	bool RemoveOne();
	
};

template<class T>
inline void SequencedShow<T>::Update(float delta)
{
	TickCounter += delta;
	if (modf(TickCounter / TickInterval, &delta) > 0.06)
		return;

	if (GoalSwitch && TickCounter > ShowedDelay)
	{
		if (!RemoveOne())
		{
			TickCounter = 0;
			GoalSwitch = 0;
			return;
		}
	}

	if (!GoalSwitch && TickCounter > HiddenDelay)
	{
		if (!AddOne())
		{
			TickCounter = 0;
			GoalSwitch = 1;
			return;
		}
	}
}

template<class T>
inline bool SequencedShow<T>::AddOne()
{
	if (MotifListRef->size() >= MotifNumber)
		return false;
	else
	{
		MotifListRef->push_front(new T());
		MotifListRef->front()->Run();
	}
	return true;
}

template<class T>
inline bool SequencedShow<T>::RemoveOne()
{
	if (MotifListRef->empty())
		return false;
	else
	{
		delete MotifListRef->front();
		MotifListRef->pop_front();
	}
	return true;
}

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

	{
		IMotifExposition<T>::MotifAmount = MotifAmount;
		IMotifExposition<T>::MotifBuffer_it = MotifBuffer.begin();
	}

	virtual void Run();
	virtual void Update();

protected:
	int MotifIndex;
	float TickCounter;
	bool GoalSwitch;
	float ShowedDelay;
	float HiddenDelay;
	float TickInterval;

	virtual bool CreateOne();
	virtual bool Show();
	virtual bool Hide();
	void ScheduleUpdate(float TickInterval, string Name, _FX Func);

	virtual void DestroyAll();

};

template<class T>
inline void MotifExposition<T>::Run()
{
	for (int i = 0; i < MotifAmount; i++)
	{
		CreateOne();
	}

	ScheduleUpdate(TickInterval, "MainPoliformUpdate")
}

template<class T>
inline void MotifExposition<T>::Update()
{
	if (!CreateOne())
	{
		TickCounter += TickInterval;

		if (GoalSwitch && TickCounter > ShowedDelay)
		{
			if (!Hide())
			{
				TickCounter = 0;
				GoalSwitch = 0;
				return;
			}
		}

		if (!GoalSwitch && TickCounter > HiddenDelay)
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

template<class T>
inline void MotifExposition<T>::DestroyAll()
{

}

template<class T>
inline void MotifExposition<T>::ScheduleUpdate(float TickInterval, string Name, _FX Func)
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(
		cocos2d::ccSchedulerFunc(std::bind(Func, this)),
		this, TickInterval, 0, Name);
}