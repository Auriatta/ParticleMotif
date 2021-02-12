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

	Emitter_Settings.SortActionSequence();
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

	Emitter_Settings.SortActionSequence();
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
			Emitter_Settings.ConvertToSingleValueSettings(&Ptrl_Settings),
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
		const std::vector<ParticleSettings<2>>* NewParticleSettings = &Emitter_Settings.ParticleSettingsScope;
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
				Ptrl_Settings = Emitter_Settings.RandParticleSettingsFromeScope();
			else
				Ptrl_Settings = (*NewParticleSettings)[SettingIndex];
		}
	}
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



ParticleSettings<2>& EmitterSettings::RandParticleSettingsFromeScope()
{
	const int SettingSize = ParticleSettingsScope.size();
	const auto RandIndex = [this](int size)->int {return cocos2d::RandomHelper::random_int(0, (size - 1)); };

	return ParticleSettings<2>({
		(ParticleSettingsScope)[RandIndex(SettingSize)].BeginFillColor,
		(ParticleSettingsScope)[RandIndex(SettingSize)].BeginBorderColor,
		(ParticleSettingsScope)[RandIndex(SettingSize)].BeginBorderWith,
		(ParticleSettingsScope)[RandIndex(SettingSize)].BeginScale,
		(ParticleSettingsScope)[RandIndex(SettingSize)].BeginRotation,
		(ParticleSettingsScope)[RandIndex(SettingSize)].FadeOutDuration,
		(ParticleSettingsScope)[RandIndex(SettingSize)].LifeTime,
		});
	
}

void EmitterSettings::SortActionSequence()
{
	ActionSequence.sort([](ParticleAction& PA1, ParticleAction& PA2)
		{
			if (PA1.when == ProcStatus::Begin &&
				PA2.when == ProcStatus::End || 
				PA1.when == ProcStatus::Begin &&
				PA2.when == ProcStatus::Begin)
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

	const cocos2d::Size RandSize = cocos2d::Size(RandRange(ParticleSetings->BeginScale[0].width, ParticleSetings->BeginScale[1].width),
		RandRange(ParticleSetings->BeginScale[0].height, ParticleSetings->BeginScale[1].height));
	
	return ParticleSettings<1>({
		ParticleSetings->BeginFillColor,
		ParticleSetings->BeginBorderColor,
		RandRange(ParticleSetings->BeginBorderWith[0],ParticleSetings->BeginBorderWith[1]),
		RandSize,
		RandRange(ParticleSetings->BeginRotation[0], ParticleSetings->BeginRotation[1]),
		RandRange(ParticleSetings->FadeOutDuration[0],ParticleSetings->FadeOutDuration[1]),
		RandRange(ParticleSetings->LifeTime[0],ParticleSetings->LifeTime[1])
		});
}
