#pragma once
#include "cocos2d.h"
#include "Particle.h"

/*
SettingsCopyEntirety: Copy entire setting stuct
RandSettings: Rand settings from vector
RandVertiesShapes: Rand verties from vector
*/
struct EmitterSettings
{
	std::vector<ParticleSettings<2>> ParticleSettingsScope;
	cocos2d::Vec4 ParticleSpawnBoundriesOffset;
	cocos2d::Vec2 Position;
	std::list<ParticleAction> ActionSequence;
	float UpdateRate = 1;
	float SettingsCopyEntirety = true;
	float RandSettings = true;
	float RandVertiesShapes = false;

	ParticleSettings<2>& RandPtrlSettings();
	void SortActionSequence();
	ParticleSettings<1> RandPtrlSettingItemsRange(ParticleSettings<2>*ParticleSetings);
};



class IEmitter
{
public:
	IEmitter()
	{}

	virtual void Init() = 0;
	virtual void Destroy() = 0;

	
protected:
	virtual void Update() = 0;
	virtual void SetPtrlSettings() = 0;

	ParticleSettings<2> Ptrl_Settings;
	EmitterSettings Emitter_Settings;

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


protected:
	int LifeCounter;
	int SettingIndex;
	int ShapeVertiesIndex;
	cocos2d::Action* Life;
	std::vector < std::vector<cocos2d::Point>> ShapeVertiesList;
	std::list<std::unique_ptr<IParticle, ParticleDeleter>> Prtl_Buffer;


	virtual void Update() override;
	virtual void SetPtrlSettings() override;


	std::vector<cocos2d::Point> GetVertiesFromShapeList();
	cocos2d::Vec2 GetNewPosition();

	void UpdateSettingsIndex();
	void UpdateVertiesShapesIndex();
};







