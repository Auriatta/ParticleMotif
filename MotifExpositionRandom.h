#pragma once


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
