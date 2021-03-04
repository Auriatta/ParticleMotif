#pragma once
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

#include "cocos2d.h"
#include "Particle.h"


/*
@PARAM SettingsCopyEntirety: Copy entire setting struct or every element separately

@PARAM RandParticleSettings: Randomise ParticleSettingsScope index based on container size

@PARAM RandVertiesShapes: Randomise VertiesShapes index based on container size

@PARAM RandGlobalIndex: Randomise index once globally, for VertiesShapes and ParticleSettingsScope
Required:
- ParticleSettingsScope and VertiesShapes SAME containers size
- ShuffleParticleSettingsElements set to FALSE
RandParticleSettings and RandVertiesShapes options will be OVERRIDE
*/
struct EmitterSettings
{
	std::vector<ParticleSettings<2>> ParticleSettingsScope;
	cocos2d::Vec4 ParticleSpawnBoundriesOffset;
	cocos2d::Vec2 Position;
	std::list<ParticleAction> ActionSequence;
	float UpdateRate = 1;
	bool ShuffleParticleSettingsElements = false;
	bool RandParticleSettings = false;
	bool RandVertiesShapes = false;
	bool RandGlobalIndex = false;

	ParticleSettings<2>& RandParticleSettingsFromScope();
	void SortActionSequence();
	ParticleSettings<1> ConvertToSingleValueSettings(ParticleSettings<2>*ParticleSetings);
};



class IEmitter
{
public:
	IEmitter()
	{}

	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual void SpawnNewParticle() = 0;

	EmitterSettings* GetEmitterSettings() { return &EmitterSettings_; };

	static enum class DestroyStatus
	{
		None,
		Waiting,
		Ready
	};

protected:
	virtual void Update() = 0;
	virtual void BuildParticleSettings() = 0;

	

	ParticleSettings<2> ParticleSettings_;
	EmitterSettings EmitterSettings_;
};



struct ParticleDeleter {
	void operator() (IParticle* p) {
		if(!p->isAvailable())
		delete p;
	}
};

class Emitter : public IEmitter
{
public:
	Emitter(EmitterSettings *emitter_settings,
		std::vector < cocos2d::Vec2> verties);
	Emitter(EmitterSettings *emitter_settings,
		std::vector < std::vector<cocos2d::Vec2>> vertiesList);


	virtual void Init() override;
	virtual void Destroy();

private: ~Emitter();

protected:
	
	DestroyStatus DestroyStatus_;
	bool ReadyToDestroy;
	int ParticleSettingsIndex;
	int ShapeVertiesIndex;
	cocos2d::Action* Life;
	std::vector < std::vector<cocos2d::Point>> ShapeVertiesList;
	std::list<std::unique_ptr<IParticle, ParticleDeleter>> ParticleBuffer;


	virtual void Update() override;
	virtual void BuildParticleSettings() override;
	virtual void SpawnNewParticle() override;

	void CheckDestroyStatus();

	std::vector<cocos2d::Point> GetVertiesFromShapeList();
	cocos2d::Vec2 GetNewPosition();

	
	bool isOneTimeRandAvailable();
	
	void RandOneTimeIndex();
	void RandVertiesShapesIndex();
	void RandSettingsIndex();

	void UpdateSettingsIndex();
	void UpdateVertiesShapesIndex();
};







