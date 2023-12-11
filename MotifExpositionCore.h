#pragma once


#include "PreDefines.h"
#include"cocos2d.h"
#include <string>
#include <mutex>
#include <thread>

template<typename T_Motif>
class IMotifExposition
{
public:
	IMotifExposition()
	{};
	virtual void Run() = 0;
	virtual void Update() = 0;
	std::list<T_Motif*>* GetMotifList() { return &MotifBuffer;  };

protected:
	virtual bool RunCreator() = 0;
	virtual void CreateOne() = 0;
	virtual bool Show() = 0;
	virtual bool Hide() = 0;


	int MotifAmount = 0;
	std::list<T_Motif*> MotifBuffer;
	typename std::list<T_Motif*>::iterator MotifBuffer_it;

	enum class RunState
	{
		Hide,
		Show
	};
};

template<class T_Motif>
class MotifExposition : public IMotifExposition<T_Motif>
{
public:
	MotifExposition(float DelayToShow, float DelayToHide,
		int MotifAmount = 1, float TickInterval = 0.2)
		: TickInterval(TickInterval), DelayToShow(DelayToShow), DelayToHide(DelayToHide),
		ScheduleName("MainUpdate"), TickCounter(0), VisibleStateGoal(RunState::Hide)
	{
		IMotifExposition<T_Motif>::MotifAmount = MotifAmount;
		
	}
	MotifExposition(const MotifExposition<T_Motif>& Ref)
		: TickInterval(Ref.TickInterval), DelayToShow(Ref.DelayToShow),
		DelayToHide(Ref.DelayToHide),
		ScheduleName("MainUpdate"), TickCounter(0), VisibleStateGoal(RunState::Hide)
	{
		IMotifExposition<T_Motif>::MotifAmount = Ref.MotifAmount;
	}

	virtual void Run() override;
	virtual void Update() override;

protected:
	virtual bool RunCreator() override;
	virtual void CreateOne() override;
	virtual bool Show() override;
	virtual bool Hide() override;
	void SetMotifIterator();


	float TickCounter;
	float DelayToShow;
	float DelayToHide;
	float TickInterval;
	RunState VisibleStateGoal;
	std::string ScheduleName;


	std::once_flag MotifIteratorInitializer;

};


template<class T_Motif>
inline void MotifExposition<T_Motif>::Run()
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(
		cocos2d::ccSchedulerFunc(std::bind(&MotifExposition<T_Motif>::Update, this)),
		this, TickInterval, 0, ScheduleName);
}

template<class T_Motif>
inline void MotifExposition<T_Motif>::Update()
{
	if (!RunCreator())
	{
		std::call_once(MotifIteratorInitializer, 
			std::bind(&MotifExposition<T_Motif>::SetMotifIterator, this));

		TickCounter += TickInterval;
		
		if (VisibleStateGoal == RunState::Hide && TickCounter > DelayToHide)
		{
			if (!Hide())
			{
				TickCounter = 0;
				VisibleStateGoal = RunState::Show;
				SetMotifIterator();
				return;
			}
		}

		if (VisibleStateGoal == RunState::Show && TickCounter > DelayToShow)
		{
			if (!Show())
			{
				TickCounter = 0;
				VisibleStateGoal = RunState::Hide;
				SetMotifIterator();
				return;
			}
		}
	}
}

template<class T_Motif>
inline bool MotifExposition<T_Motif>::RunCreator()
{
	if (MotifBuffer.size() >= MotifAmount)
		return false;
	else
	{
		CreateOne();
	}
	return true;
}

template<class T_Motif>
inline void MotifExposition<T_Motif>::CreateOne()
{

	MotifBuffer.push_front(new T_Motif());
	MotifBuffer.front()->Init();
	MotifBuffer.front()->Run();

}

template<class T_Motif>
inline bool MotifExposition<T_Motif>::Show()
{
	(*MotifBuffer_it)->TurnOnAllEmitters();
	MotifBuffer_it++;
	if (MotifBuffer_it == MotifBuffer.end())
		return false;
	return true;
}

template<class T_Motif>
inline bool MotifExposition<T_Motif>::Hide()
{
	(*MotifBuffer_it)->TurnOffAllEmitters();
	if (MotifBuffer_it == MotifBuffer.begin())
		return false;
	MotifBuffer_it--;
	return true;
}

template<class T_Motif>
inline void MotifExposition<T_Motif>::SetMotifIterator()
{
	if (VisibleStateGoal == RunState::Hide)
	{
		MotifBuffer_it = MotifBuffer.end();
		MotifBuffer_it--;
	}
	else if(VisibleStateGoal == RunState::Show)
		MotifBuffer_it = MotifBuffer.begin();
}




