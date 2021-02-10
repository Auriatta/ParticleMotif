#include "MPoliform.h"

MPoliform::MPoliform()
{
	CreateEmitter_1();

	
};
	
	

void MPoliform::Update()
{

}

MPoliform::~MPoliform()
{
	delete emitter_1;
}

void MPoliform::CreateEmitter_1()
{
	std::vector < std::vector<cocos2d::Vec2>> vertiesList;
	vertiesList.push_back({
	cocos2d::Vec2(30, 0),
	cocos2d::Vec2(30, -30),
	cocos2d::Vec2(0, -30),
	cocos2d::Vec2(0, 0) });
	vertiesList.push_back({
		cocos2d::Vec2(0,0),
		cocos2d::Vec2(-25,25) ,
		cocos2d::Vec2(25,25) });

	ParticleSettings prtl_s_1;
	prtl_s_1.BeginBorderColor = cocos2d::Color4B::ORANGE;
	prtl_s_1.BeginFillColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s_1.BeginBorderWith = 1.2;
	prtl_s_1.BeginRotation = 0;
	prtl_s_1.BeginScale = cocos2d::Size(1,1);
	prtl_s_1.FadeOutDuration = 0.5;
	prtl_s_1.LifeTime = 4;

	ParticleSettings prtl_s_2;
	prtl_s_2.BeginFillColor = cocos2d::Color4B::WHITE;
	prtl_s_2.BeginBorderWith = 0;
	prtl_s_2.BeginRotation = 45;
	prtl_s_2.BeginScale = cocos2d::Size(1, 1);
	prtl_s_2.FadeOutDuration = 2;
	prtl_s_2.LifeTime = 4;


	EmitterSettings emitter_s;
	emitter_s.ParticleSettingsScope.push_back(prtl_s_1);
	emitter_s.ParticleSettingsScope.push_back(prtl_s_2);
	emitter_s.ParticleSpawnBoundriesOffset = cocos2d::Vec4(-70, -70, 150, 150);
	emitter_s.Position = cocos2d::Vec2(500, 500);
	emitter_s.UpdateRate = 1;
	emitter_s.ActionSequence.push_back(
		ParticleAction{ [this]()->cocos2d::Action* {return cocos2d::FadeIn::create(1); }, ProcStatus::Begin });
	emitter_s.RandSettings = false;
	emitter_s.RandVertiesShapes = false;
	emitter_s.SettingsCopyEntirety = true;

	emitter_1 = new Emitter(&emitter_s, vertiesList);
	emitter_1->Init();
}
