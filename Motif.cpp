#include "Motif.h"
#include "MainScene.h"

void Motif::Run()
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(
		cocos2d::ccSchedulerFunc(std::bind(&Motif::Update, this)), 
		this,
		RefreshRate,
		0, "MotifUpdateProcess");
}

void Motif::Destroy()
{
	Motif::~Motif();
}

Motif::~Motif()
{
	cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
}

void Motif::Update()
{
}
