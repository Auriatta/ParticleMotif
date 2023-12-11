#pragma once

#include "MotifExpositionCore.h"
#include <mutex>
#include <thread>


class IMotifExpositionMultiTick 
{
	/*
	* @Param TickIntervalShow - Refresh rate for single motif at showing status
	* @Param TickIntervalHide - Refresh rate for single motif at hiding status
	* @param TickIntervalInit - Refresh rate for single motif creation (TickInterval Inherite from MotifExposition)
	*/
public:
	IMotifExpositionMultiTick()
	{};

protected:
	virtual void SwitchToTickIntervalShow() = 0;
	virtual void SwitchToTickIntervalHide() = 0;
	virtual void SwitchToTickIntervalInit() = 0;

	float TickIntervalShow = 0;
	float TickIntervalHide = 0;

};

template<class T_Motif>
class MotifExpositionMultiTick : public IMotifExpositionMultiTick, public MotifExposition<T_Motif>
{
public:
	MotifExpositionMultiTick(MotifExposition<T_Motif> &Base,
		float TickIntervalShow = 0.2,
		float TickIntervalHide = 0.2)
		:
		MotifExposition<T_Motif>(Base),
		ShowSwitchOnceFlag(std::make_unique<std::once_flag>())
	{	
		IMotifExpositionMultiTick::TickIntervalHide = TickIntervalHide;
		IMotifExpositionMultiTick::TickIntervalShow = TickIntervalShow;
		MotifExposition<T_Motif>::VisibleStateGoal = RunState::Show;
		MotifExposition<T_Motif>::TickCounter = MotifExposition<T_Motif>::DelayToShow;
	};

	virtual void Run() override;
	virtual void Update() override;

protected:
	virtual void SwitchToTickIntervalShow() override;
	virtual void SwitchToTickIntervalHide() override;
	virtual void SwitchToTickIntervalInit() override;

	void ChangeTickInterval(
		float TickInterval, std::string ScheduleName);


	std::unique_ptr<std::once_flag> HideSwitchOnceFlag;
	std::unique_ptr<std::once_flag> ShowSwitchOnceFlag;

};

template<class T_Motif>
inline void MotifExpositionMultiTick<T_Motif>::Update()
{
	if (MotifBuffer.size() >= MotifExposition<T_Motif>::MotifAmount)
	{
		if (MotifExposition<T_Motif>::VisibleStateGoal == RunState::Hide)
		{
			std::call_once(*HideSwitchOnceFlag, 
				std::bind(&MotifExpositionMultiTick<T_Motif>::SwitchToTickIntervalHide,
				this));
		}
		else if(MotifExposition<T_Motif>::VisibleStateGoal == RunState::Show)
			std::call_once(*ShowSwitchOnceFlag,
				std::bind(&MotifExpositionMultiTick<T_Motif>::SwitchToTickIntervalShow,
					this));
	}

	MotifExposition<T_Motif>::Update();
}

template<class T_Motif>
inline void MotifExpositionMultiTick<T_Motif>::Run()
{
	MotifExpositionMultiTick<T_Motif>::SwitchToTickIntervalInit();
}

template<class T_Motif>
inline void MotifExpositionMultiTick<T_Motif>::SwitchToTickIntervalInit()
{
	ChangeTickInterval(MotifExposition<T_Motif>::TickInterval,
		MotifExposition<T_Motif>::ScheduleName);
}

template<class T_Motif>
inline void MotifExpositionMultiTick<T_Motif>::SwitchToTickIntervalShow()
{
	ChangeTickInterval(IMotifExpositionMultiTick::TickIntervalShow,
		MotifExposition<T_Motif>::ScheduleName);

	HideSwitchOnceFlag.reset();
	HideSwitchOnceFlag = std::make_unique<std::once_flag>();
}

template<class T_Motif>
inline void MotifExpositionMultiTick<T_Motif>::SwitchToTickIntervalHide()
{
	ChangeTickInterval(IMotifExpositionMultiTick::TickIntervalHide,
		MotifExposition<T_Motif>::ScheduleName);

	ShowSwitchOnceFlag.reset();
	ShowSwitchOnceFlag = std::make_unique<std::once_flag>();

}

template<class T_Motif>
inline void MotifExpositionMultiTick<T_Motif>::ChangeTickInterval(
	float TickInterval, std::string ScheduleName)
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(
		cocos2d::ccSchedulerFunc(std::bind(&IMotifExposition::Update,
			this)),
		this, TickInterval, 0, ScheduleName);
}
