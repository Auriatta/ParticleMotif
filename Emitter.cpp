#include "Emitter.h"
#include "MainScene.h"

Emitter::Emitter(EmitterSettings *emitter_settings,
	std::vector < cocos2d::Point> verties)
	: LifeCounter(0), Life(nullptr), 
	ShapeVertiesList(std::vector < std::vector<cocos2d::Point>>({verties})),
	SettingIndex(0), ShapeVertiesIndex(0)
{
	if (emitter_settings->ParticleSettingsScope.empty())
		assert("ParticleSettingsScope is Empty");

	if(emitter_settings->ParticleSettingsScope.size() == 1)
		Ptrl_Settings = emitter_settings->ParticleSettingsScope[0];
	
	Emitter_Settings = *emitter_settings;

	SortActionSequence();
}

Emitter::Emitter(EmitterSettings *emitter_settings,
	std::vector < std::vector<cocos2d::Point>> vertiesList)
	: Life(nullptr), ShapeVertiesList(vertiesList),
	SettingIndex(0), ShapeVertiesIndex(0)
{
	if (emitter_settings->ParticleSettingsScope.empty())
		assert("ParticleSettingsScope is Empty");

	if (emitter_settings->ParticleSettingsScope.size() == 1)
		Ptrl_Settings = emitter_settings->ParticleSettingsScope[0];
	
	Emitter_Settings = *emitter_settings;

	SortActionSequence();
}

void Emitter::Init()
{
	Update();

	Life = cocos2d::RepeatForever::create(
		cocos2d::Sequence::create(
		cocos2d::DelayTime::create(Emitter_Settings.UpdateRate),
		cocos2d::CallFunc::create(std::bind(&Emitter::Update, std::ref(*this))),
		nullptr));

	Update();
	cocos2d::Director::getInstance()->getRunningScene()->runAction(Life);
}

void Emitter::Destroy()
{
	Prtl_Buffer.clear();
	cocos2d::Director::getInstance()->getRunningScene()->stopAction(Life);
	delete this;
}


	
void Emitter::Update()
{
	SetPtrlSettings();

	Prtl_Buffer.push_back(std::unique_ptr<IParticle, ParticleDeleter>(
		new Particle(
			Ptrl_Settings,
			GetNewPosition(),
			GetVertiesFromShapeList(),
			&Emitter_Settings.ActionSequence,
			true
		), ParticleDeleter()));


	if (!Emitter_Settings.RandSettings)
		UpdateSettingsIndex();

	if (!Emitter_Settings.RandVertiesShapes)
		UpdateVertiesShapesIndex();
}

void Emitter::SetPtrlSettings()
{
	if (Emitter_Settings.ParticleSettingsScope.size() > 1)
	{
		const std::vector<ParticleSettings>* NewParticleSettings = &Emitter_Settings.ParticleSettingsScope;
		const int PtrlSettingSize = NewParticleSettings->size(); 
		
		if (Emitter_Settings.SettingsCopyEntirety)
		{
			if (Emitter_Settings.RandSettings)
			{
				const int index = cocos2d::RandomHelper::random_int(0, (PtrlSettingSize - 1));
				Ptrl_Settings = (*NewParticleSettings)[index];
			}
			else
			{
				Ptrl_Settings = (*NewParticleSettings)[SettingIndex];
			}
		}
		else
		{
			if(Emitter_Settings.RandSettings)
				RandPtrlSettings();
			else
				Ptrl_Settings = (*NewParticleSettings)[SettingIndex];
		}
	}
}

void Emitter::RandPtrlSettings()
{
	const std::vector<ParticleSettings>* NewParticleSettings = &Emitter_Settings.ParticleSettingsScope;
	const int NewSettingSize = NewParticleSettings->size();

	auto RandIndex = [this](int size)->int {return cocos2d::RandomHelper::random_int(0, (size - 1)); };
	
	Ptrl_Settings.BeginBorderColor = (*NewParticleSettings)[RandIndex(NewSettingSize)].BeginBorderColor;
	Ptrl_Settings.BeginFillColor = (*NewParticleSettings)[RandIndex(NewSettingSize)].BeginFillColor;
	Ptrl_Settings.BeginBorderWith = (*NewParticleSettings)[RandIndex(NewSettingSize)].BeginBorderWith;
	Ptrl_Settings.BeginRotation = (*NewParticleSettings)[RandIndex(NewSettingSize)].BeginRotation;
	Ptrl_Settings.BeginScale = (*NewParticleSettings)[RandIndex(NewSettingSize)].BeginScale;
	Ptrl_Settings.FadeOutDuration = (*NewParticleSettings)[RandIndex(NewSettingSize)].FadeOutDuration;
	Ptrl_Settings.LifeTime = (*NewParticleSettings)[RandIndex(NewSettingSize)].LifeTime;
}

void Emitter::SortActionSequence()
{
	Emitter_Settings.ActionSequence.sort([](ParticleAction& PA1, ParticleAction& PA2)
		{
			if (PA1.when == ProcStatus::End &&
				PA2.when == ProcStatus::Begin)
				return true;
			else return false;
		});
}

std::vector<cocos2d::Point> Emitter::GetVertiesFromShapeList()
{
	if (Emitter_Settings.RandVertiesShapes)
		return ShapeVertiesList.at(
			cocos2d::RandomHelper::random_int(0, (int)ShapeVertiesList.size() - 1)
		);
	else
		return ShapeVertiesList.at(ShapeVertiesIndex);
}

cocos2d::Vec2 Emitter::GetNewPosition()
{
	return {
		cocos2d::RandomHelper::random_real<float>(
			Emitter_Settings.Position.x + Emitter_Settings.ParticleSpawnBoundriesOffset.x,
			Emitter_Settings.Position.x + Emitter_Settings.ParticleSpawnBoundriesOffset.w),
		cocos2d::RandomHelper::random_real<float>(
			Emitter_Settings.Position.y + Emitter_Settings.ParticleSpawnBoundriesOffset.y,
			Emitter_Settings.Position.y + Emitter_Settings.ParticleSpawnBoundriesOffset.z) };
}

void Emitter::UpdateSettingsIndex()
{
	SettingIndex += 1;
	if (SettingIndex > Emitter_Settings.ParticleSettingsScope.size() - 1)
		SettingIndex = 0;
}

void Emitter::UpdateVertiesShapesIndex()
{
	ShapeVertiesIndex += 1;
	if (ShapeVertiesIndex > ShapeVertiesList.size() - 1)
		ShapeVertiesIndex = 0;
}
