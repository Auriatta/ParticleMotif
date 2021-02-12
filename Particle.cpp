#include "Particle.h"
#include "MainScene.h"
#include <algorithm>


Particle::Particle(ParticleSettings<1>& settings, cocos2d::Vec2 beginPosition,
	std::vector<cocos2d::Vec2> ShapeVerties,
	std::list<ParticleAction>* ActionSequence, bool autoSpawn)
{
	IParticle::isAvailable_ = false;

	FadeOutDuration = settings.FadeOutDuration[0];
	LifeTime = settings.LifeTime[0];

	this->ActionSequence = ActionSequence;
	
	
	shape = cocos2d::DrawNode::create();
	shape->setPosition(beginPosition);
	shape->setScale(settings.BeginScale[0].width, settings.BeginScale[0].height);
	shape->setRotation(settings.BeginRotation[0]);

	shape->drawPolygon(ShapeVerties.data(), ShapeVerties.size(),
		cocos2d::Color4F(settings.BeginFillColor), settings.BeginBorderWith[0],
		cocos2d::Color4F(settings.BeginBorderColor)); 
	shape->setOpacity(0);

	if (autoSpawn)
		Spawn();
}


void Particle::Destroy()
{
	if (shape != nullptr && isAvailable())
	{
		isAvailable_ = false;

		shape->runAction(cocos2d::Sequence::create(cocos2d::FadeOut::create(FadeOutDuration),
			cocos2d::CallFunc::create([this]() {
				if (shape != nullptr)
					this->~Particle();
				}),
			nullptr));
	}
}

bool Particle::isAvailable()
{
	return isAvailable_;
}

void Particle::Finish()
{
	RunSpecificActionSequence(ProcStatus::End);
	
	cocos2d::Action* KillCheck = cocos2d::RepeatForever::create(
		cocos2d::Sequence::create(
			cocos2d::DelayTime::create(0.2),
			cocos2d::CallFunc::create(
				[this, KillCheck]() {

					if (!this->isAnyActionRuning(ProcStatus::End) && this->isAvailable())
					{
						this->Destroy();
					}
						

				}), nullptr));


	shape->runAction(KillCheck);
}

void Particle::Spawn()
{
	
	cocos2d::Director::getInstance()->getRunningScene()->addChild(shape, 1);
	

	shape->runAction(cocos2d::Sequence::create(
		cocos2d::DelayTime::create(LifeTime),
		cocos2d::CallFunc::create(std::bind(&Particle::Finish, std::ref(*this))),
		nullptr));

	RunSpecificActionSequence(ProcStatus::Begin);
	isAvailable_ = true;
}

bool Particle::isAnyActionRuning(ProcStatus status)
{
	return (shape->getActionByTag((int)status));
}

Particle::~Particle()
{
	if (shape != nullptr)
		shape->stopAllActions();
	ClearShape();
}

void Particle::ClearShape()
{
	if (shape != nullptr)
	{
		shape->clear();
		shape->cleanup();
		cocos2d::Director::getInstance()->getRunningScene()->removeChild(shape);
		shape = nullptr;
	}
}

void Particle::RunSpecificActionSequence(ProcStatus status)
{
	cocos2d::Action* newAction = nullptr;
	for (ParticleAction& action : *ActionSequence)
	{
		if (action.when == status)
		{
			newAction = action.action();
			newAction->setTag((int)status);
			shape->runAction(newAction);
		}
	}
}

