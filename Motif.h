#pragma once
#include "cocos2d.h"

class IMotif
{
public: 
	virtual void Run() = 0;

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

	~Motif();

protected:
	float RefreshRate;

	virtual void Update() override;
};