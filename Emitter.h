#pragma once


#include "cocos2d.h"
#include "Particle.h"


/*
@PARAM SettingsCopyEntirety: Copy entire setting struct or every element separately

@PARAM RandParticleSettings: Randomize ParticleSettingsScope index based on container size

@PARAM RandVertiesShapes: Randomize VertiesShapes index based on container size

@PARAM RandGlobalIndex: Randomize index once globally, for VertiesShapes and ParticleSettingsScope
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
	virtual void Stop() = 0;
	virtual void Play() = 0;

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
	virtual void Play() override;
	virtual void Stop() override;

private: ~Emitter();

protected:
	
	DestroyStatus DestroyStatus_;
	bool isPaused;
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







