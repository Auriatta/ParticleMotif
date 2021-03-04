#pragma once
#include "PreDefines.h"
#include"cocos2d.h"

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