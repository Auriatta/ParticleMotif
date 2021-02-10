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

struct ParticleSettings
{
	cocos2d::Color4B BeginFillColor = cocos2d::Color4B::YELLOW;
	cocos2d::Color4B BeginBorderColor = cocos2d::Color4B::MAGENTA;
	float BeginBorderWith = 1;
	cocos2d::Size BeginScale = { 1,1 };
	float BeginRotation = 0;
	float FadeOutDuration = 0.3f;
	float LifeTime = 3;
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

protected:
	virtual void ClearShape() = 0;

	cocos2d::DrawNode* shape = nullptr;
	bool isAvailable_ = 0;
};


class Particle : public IParticle
{
public:
	Particle(ParticleSettings& settings, cocos2d::Vec2 beginPosition,
		std::vector<cocos2d::Vec2> ShapeVerties,
		std::list<ParticleAction>* ActionSequence, bool autoSpawn = false);

	virtual void Destroy() override;
	virtual bool isAvailable() override;
	virtual void Finish() override;
	virtual void Spawn() override;
	bool Particle::isAnyActionRuning(ProcStatus);

	~Particle();

protected:
	std::list<ParticleAction>* ActionSequence;
	float FadeOutDuration;
	float LifeTime;

	virtual void ClearShape() override;
	void RunSpecificActionSequence(ProcStatus);
};



