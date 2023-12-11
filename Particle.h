

#pragma once
#include "cocos2d.h"


enum class ProcStatus : short
{
	Begin = 'B'+'e'+'g'+'i'+'n',
	End = 'E' + 'n' + 'd',
	None = 'N' + 'o' + 'n'
};


struct ParticleAction
{
	std::function<cocos2d::Action* ()> action;
	ProcStatus when;
};



template<int Size>
struct ParticleSettings
{
	cocos2d::Color4B BeginFillColor = cocos2d::Color4B::WHITE;
	cocos2d::Color4B BeginBorderColor = cocos2d::Color4B::BLACK;
	std::array<float, Size> BeginBorderWith;
	std::array<float, Size> BeginScale;
	std::array<float, Size> BeginRotation;
	std::array<float, Size> FadeOutDuration;
	std::array<float, Size> LifeTime;
	std::array<int, Size>	ZOrderIndex;
};


class IParticle
{
public:
	IParticle()
	{}

	virtual void Spawn() = 0;
	virtual void Destroy() = 0;
	virtual void Finish() = 0;
	virtual bool isAvailable()=0;
	virtual bool isNull() = 0;

protected:
	virtual void ClearShape() = 0;

	cocos2d::DrawNode* shape = nullptr;
	bool isAvailable_ = 0;
};


class Particle : public IParticle
{
public:
	Particle(ParticleSettings<1>& settings, cocos2d::Vec2 beginPosition,
		std::vector<cocos2d::Vec2> ShapeVerties,
		std::list<ParticleAction>* ActionSequence, bool autoSpawn = false);

	virtual void Destroy() override;
	virtual bool isAvailable() override;
	virtual void Finish() override;
	virtual void Spawn() override;
	virtual bool isNull() override;
	bool Particle::isAnyActionRuning(ProcStatus);

	~Particle();

protected:
	std::list<ParticleAction>* ActionSequence;
	float FadeOutDuration;
	float LifeTime;
	int ZOrderIndex;

	virtual void ClearShape() override;
	void RunSpecificActionSequence(ProcStatus);
};



