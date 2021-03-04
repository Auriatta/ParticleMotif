/*
* Copyright (c) <2021> <Alex 'Auriatta' Ates>.
All rights reserved.

Redistribution and use in source and binary forms are permitted provided
that the above copyright notice and this paragraph are duplicated in all
such forms and that any documentation, advertising materials, and other
materials related to such distribution and use acknowledge that the software
was developed by the <Alex 'Auriatta' Ates>.
The name of the <Alex 'Auriatta' Ates> may not be used to endorse or promote
products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED ``AS IS'' AND
WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE.
* Contact me at Auriattadev.com
*/

#include "Emitter.h"
#include "MainScene.h"

Emitter::Emitter(EmitterSettings *emitter_settings,
	std::vector < cocos2d::Point> verties)
	: Life(nullptr), 
	ShapeVertiesList(std::vector < std::vector<cocos2d::Point>>({verties})),
	ParticleSettingsIndex(0), ShapeVertiesIndex(0),
	DestroyStatus_(DestroyStatus::None)
{
	if (emitter_settings->ParticleSettingsScope.empty())
		std::runtime_error("ParticleSettingsScope is Empty");

	if(emitter_settings->ParticleSettingsScope.size() == 1)
		ParticleSettings_ = emitter_settings->ParticleSettingsScope[0];
	
	EmitterSettings_ = *emitter_settings;

	EmitterSettings_.SortActionSequence();
}

Emitter::Emitter(EmitterSettings *emitter_settings,
	std::vector < std::vector<cocos2d::Point>> vertiesList)
	: Life(nullptr), ShapeVertiesList(vertiesList),
	ParticleSettingsIndex(0), ShapeVertiesIndex(0),
	DestroyStatus_(DestroyStatus::None)
{
	if (emitter_settings->ParticleSettingsScope.empty())
		std::runtime_error("ParticleSettingsScope is Empty");

	if (emitter_settings->ParticleSettingsScope.size() == 1)
		ParticleSettings_ = emitter_settings->ParticleSettingsScope[0];
	
	EmitterSettings_ = *emitter_settings;

	EmitterSettings_.SortActionSequence();
}

void Emitter::Init()
{
	Life = cocos2d::RepeatForever::create(
		cocos2d::Sequence::create(
		cocos2d::DelayTime::create(EmitterSettings_.UpdateRate),
		cocos2d::CallFunc::create(std::bind(&Emitter::Update, std::ref(*this))),
		nullptr));

	cocos2d::Director::getInstance()->getRunningScene()->runAction(Life);

	Update();
}

void Emitter::Destroy()
{
	DestroyStatus_ = DestroyStatus::Waiting;
}

Emitter::~Emitter()
{
	ParticleBuffer.clear();
	cocos2d::Director::getInstance()->getRunningScene()->stopAction(Life);
	delete this;
}

void Emitter::Update()
{
	if (DestroyStatus_ == DestroyStatus::None)
	{
		BuildParticleSettings();

		SpawnNewParticle();
	}
	else
		CheckDestroyStatus();

	
}

void Emitter::BuildParticleSettings()
{
	if (EmitterSettings_.ParticleSettingsScope.size() > 1)
	{
		const std::vector<ParticleSettings<2>>* NewParticleSettings = &EmitterSettings_.ParticleSettingsScope;
		
		if (isOneTimeRandAvailable())
			RandOneTimeIndex();
		else
		{
			if (!EmitterSettings_.RandVertiesShapes)
				UpdateVertiesShapesIndex();
			else
				RandVertiesShapesIndex();


			if (!EmitterSettings_.RandParticleSettings)
				UpdateSettingsIndex();
			else
			{
				if (EmitterSettings_.ShuffleParticleSettingsElements)
				{
					ParticleSettings_ = EmitterSettings_.RandParticleSettingsFromScope();
					return;
				}
				else
					RandSettingsIndex();
			}
		}

		ParticleSettings_ = (*NewParticleSettings)[ParticleSettingsIndex];
	}
}

void Emitter::SpawnNewParticle()
{
	ParticleBuffer.push_back(std::unique_ptr<IParticle, ParticleDeleter>(
		new Particle(
			EmitterSettings_.ConvertToSingleValueSettings(&ParticleSettings_),
			GetNewPosition(),
			GetVertiesFromShapeList(),
			&EmitterSettings_.ActionSequence,
			true
		), ParticleDeleter()));
}

void Emitter::CheckDestroyStatus()
{
	switch (DestroyStatus_)
	{
	case DestroyStatus::Waiting:
		if (ParticleBuffer.empty())
			DestroyStatus_ = DestroyStatus::Ready;
		else
			break;
	
	case DestroyStatus::Ready:
		this->~Emitter();
		return;
	
	default:
		return;
	}
		

}

std::vector<cocos2d::Point> Emitter::GetVertiesFromShapeList()
{
	return ShapeVertiesList.at(ShapeVertiesIndex);
}

cocos2d::Vec2 Emitter::GetNewPosition()
{
	return {
		cocos2d::RandomHelper::random_real<float>(
			EmitterSettings_.Position.x + EmitterSettings_.ParticleSpawnBoundriesOffset.x,
			EmitterSettings_.Position.x + EmitterSettings_.ParticleSpawnBoundriesOffset.w),
		cocos2d::RandomHelper::random_real<float>(
			EmitterSettings_.Position.y + EmitterSettings_.ParticleSpawnBoundriesOffset.y,
			EmitterSettings_.Position.y + EmitterSettings_.ParticleSpawnBoundriesOffset.z) };
}

bool Emitter::isOneTimeRandAvailable()
{
	if (EmitterSettings_.RandGlobalIndex &&
		!EmitterSettings_.ShuffleParticleSettingsElements &&
		EmitterSettings_.ParticleSettingsScope.size() ==
		ShapeVertiesList.size())
		return true;
	else
		return false;
}

void Emitter::RandOneTimeIndex()
{
	int Random = 0;
	do
	{
		Random = cocos2d::RandomHelper::random_int<int>
			(0, (ShapeVertiesList.size() - 1));
	} while (ParticleSettingsIndex == Random);

	ParticleSettingsIndex = ShapeVertiesIndex = Random;
}

void Emitter::RandVertiesShapesIndex()
{
	ShapeVertiesIndex = cocos2d::RandomHelper::random_int<int>
		(0, (ShapeVertiesList.size() - 1));
}

void Emitter::RandSettingsIndex()
{
	ParticleSettingsIndex = cocos2d::RandomHelper::random_int<int>
		(0, (EmitterSettings_.ParticleSettingsScope.size() - 1));
}

void Emitter::UpdateSettingsIndex()
{
	ParticleSettingsIndex++;
	if (ParticleSettingsIndex > EmitterSettings_.ParticleSettingsScope.size() - 1)
		ParticleSettingsIndex = 0;
}

void Emitter::UpdateVertiesShapesIndex()
{
	ShapeVertiesIndex++;
	if (ShapeVertiesIndex > ShapeVertiesList.size() - 1)
		ShapeVertiesIndex = 0;
}



ParticleSettings<2>& EmitterSettings::RandParticleSettingsFromScope()
{
	const int ContainerSize = ParticleSettingsScope.size();
	const auto RandIndex = [this](int size)->int {return cocos2d::RandomHelper::random_int(0, (size - 1)); };

	return ParticleSettings<2>({
		(ParticleSettingsScope)[RandIndex(ContainerSize)].BeginFillColor,
		(ParticleSettingsScope)[RandIndex(ContainerSize)].BeginBorderColor,
		(ParticleSettingsScope)[RandIndex(ContainerSize)].BeginBorderWith,
		(ParticleSettingsScope)[RandIndex(ContainerSize)].BeginScale,
		(ParticleSettingsScope)[RandIndex(ContainerSize)].BeginRotation,
		(ParticleSettingsScope)[RandIndex(ContainerSize)].FadeOutDuration,
		(ParticleSettingsScope)[RandIndex(ContainerSize)].LifeTime,
		});
	
}

void EmitterSettings::SortActionSequence()
{
	ActionSequence.sort([](ParticleAction& PA1, ParticleAction& PA2)
		{
			if (PA1.when == ProcStatus::Begin &&
				PA2.when == ProcStatus::End)
				return true;
			else return false;
		});
}

ParticleSettings<1> EmitterSettings::ConvertToSingleValueSettings(ParticleSettings<2>* ParticleSetings)
{
	
	const auto RandRange = [this](float var1, float var2)->float 
	{
		return cocos2d::RandomHelper::random_real<float>(
			std::min(var1,var2), std::max(var1,var2));
	};


	return ParticleSettings<1>({
		ParticleSetings->BeginFillColor,
		ParticleSetings->BeginBorderColor,
		RandRange(ParticleSetings->BeginBorderWith[0],ParticleSetings->BeginBorderWith[1]),
		RandRange(ParticleSetings->BeginScale[0], ParticleSetings->BeginScale[1]),
		RandRange(ParticleSetings->BeginRotation[0], ParticleSetings->BeginRotation[1]),
		RandRange(ParticleSetings->FadeOutDuration[0],ParticleSetings->FadeOutDuration[1]),
		RandRange(ParticleSetings->LifeTime[0],ParticleSetings->LifeTime[1]),
		(int)RandRange(ParticleSetings->ZOrderIndex[0], ParticleSetings->ZOrderIndex[1])
		});
}
