

#pragma once
#include "cocos2d.h"

class IMotif
{
public: 
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void TurnOffAllEmitters() = 0;
	virtual void TurnOnAllEmitters() = 0;
	virtual void SetPosition(cocos2d::Vec2 Position) = 0;

protected:

	virtual void Update() = 0;
	virtual void Destroy() = 0;
};

class Motif : IMotif
{
public:
	Motif()
	:	RefreshRate(cocos2d::Director::getInstance()->getDeltaTime())
	{}

	virtual void Run() override;
	virtual void Destroy() override;
	virtual void SetPosition(cocos2d::Vec2 Position) override { this->Position = Position; };

	~Motif();

protected:
	float RefreshRate;
	cocos2d::Vec2 Position;

	virtual void Update() override;
};
