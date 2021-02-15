#include "MPoliform.h"

MPoliform::MPoliform()
{
	behavior = std::make_unique<AI_Basic>(AI_Basic(cocos2d::Vec2(900, 600),
		cocos2d::Vec2(10, 10)));
	RefreshRate = 0.3;
	CreateEmitter_1();
	
	
};
	
	

void MPoliform::Update()
{
	behavior->update();
	emitter_1->GetEmitterSettings()->Position = behavior->getPosition();
	cocos2d::log("Position: %f", emitter_1->GetEmitterSettings()->Position.x);
}

MPoliform::~MPoliform()
{
	delete emitter_1;
}

void MPoliform::CreateEmitter_1()
{
	
	std::vector < std::vector<cocos2d::Vec2>> vertiesList;
	const std::vector<cocos2d::Vec2> Rectangle = {
		cocos2d::Vec2(30, 0),
	cocos2d::Vec2(30, -30),
	cocos2d::Vec2(0, -30),
	cocos2d::Vec2(0, 0)
	};
	const std::vector<cocos2d::Vec2> Triangle = {
		cocos2d::Vec2(0,0),
		cocos2d::Vec2(-25,25),
		cocos2d::Vec2(25,25)
	};
	vertiesList.push_back(Rectangle);
	vertiesList.push_back(Triangle);
	vertiesList.push_back(Triangle);
	vertiesList.push_back(Triangle);
	vertiesList.push_back(Triangle);
	vertiesList.push_back(Rectangle);

	std::array<ParticleSettings<2>, 6> prtl_s;
	prtl_s[0].BeginBorderColor = cocos2d::Color4B::ORANGE;
	prtl_s[0].BeginFillColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[0].BeginBorderWith = { 1.2, 1.2 };
	prtl_s[0].BeginRotation = { 45,45 };
	prtl_s[0].BeginScale = { 0.9,1.1 };
	prtl_s[0].FadeOutDuration = { 0.6,0.9 };
	prtl_s[0].LifeTime = { 1,1 };

	prtl_s[1].BeginBorderColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[1].BeginFillColor = cocos2d::Color4B::WHITE;
	prtl_s[1].BeginBorderWith = { 0,0 };
	prtl_s[1].BeginRotation = { 0,0 };
	prtl_s[1].BeginScale = { 0.9,1.1 };
	prtl_s[1].FadeOutDuration = { 0.6,0.9 };
	prtl_s[1].LifeTime = { 1,1 };

	prtl_s[2].BeginBorderColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[2].BeginFillColor = cocos2d::Color4B::WHITE;
	prtl_s[2].BeginBorderWith = { 0,0 };
	prtl_s[2].BeginRotation = { 45,45 };
	prtl_s[2].BeginScale = { 1,1 };
	prtl_s[2].FadeOutDuration = { 0.6,0.9 };
	prtl_s[2].LifeTime = { 1,1 };

	prtl_s[3].BeginBorderColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[3].BeginFillColor = cocos2d::Color4B::WHITE;
	prtl_s[3].BeginBorderWith = { 0,0 };
	prtl_s[3].BeginRotation = { 180,180 };
	prtl_s[3].BeginScale = { 0.9,1.1 };
	prtl_s[3].FadeOutDuration = { 0.6,0.9 };
	prtl_s[3].LifeTime = { 1,1 };
	
	prtl_s[4].BeginBorderColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[4].BeginFillColor = cocos2d::Color4B::WHITE;
	prtl_s[4].BeginBorderWith = { 0,0 };
	prtl_s[4].BeginRotation = { -45,-45 };
	prtl_s[4].BeginScale = { 0.9,1.1 };
	prtl_s[4].FadeOutDuration = { 0.6,0.9 };
	prtl_s[4].LifeTime = { 1,1 };

	prtl_s[5].BeginBorderColor = cocos2d::Color4B::ORANGE;
	prtl_s[5].BeginFillColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[5].BeginBorderWith = { 1.2, 1.2 };
	prtl_s[5].BeginRotation = { 0,0 };
	prtl_s[5].BeginScale = { 0.9,1.1 };
	prtl_s[5].FadeOutDuration = { 0.6,0.9 };
	prtl_s[5].LifeTime = { 1,1 };

	EmitterSettings emitter_s;
	emitter_s.ParticleSettingsScope.push_back(prtl_s[0]);
	emitter_s.ParticleSettingsScope.push_back(prtl_s[1]);
	emitter_s.ParticleSettingsScope.push_back(prtl_s[2]);
	emitter_s.ParticleSettingsScope.push_back(prtl_s[3]);
	emitter_s.ParticleSettingsScope.push_back(prtl_s[4]);
	emitter_s.ParticleSettingsScope.push_back(prtl_s[5]);
	emitter_s.ParticleSpawnBoundriesOffset = cocos2d::Vec4(-70, -100, 100, 70);
	emitter_s.Position = cocos2d::Vec2(900,600);
	emitter_s.UpdateRate = 1;
	emitter_s.RandSettings = false;
	emitter_s.RandVertiesShapes = false;
	emitter_s.SettingsCopyEntirety = true;
	emitter_s.ActionSequence.push_back(
		ParticleAction{ [this]()->cocos2d::Action* {return cocos2d::FadeIn::create(1); }, ProcStatus::Begin });
	//emitter_s.ActionSequence.push_back(
	//	ParticleAction{ [this]()->cocos2d::Action* {return cocos2d::MoveBy::create(2,cocos2d::Vec2(0,100)); }, ProcStatus::Begin });

	emitter_1 = new Emitter(&emitter_s, vertiesList);
	emitter_1->Init();
}

cocos2d::Vec2 MPoliform::GetRandomPositionFromBorderBox()
{
	return cocos2d::Vec2(
		cocos2d::RandomHelper::random_int<int>(BORDER_X_ORIGIN, BORDER_WIDTH),
		cocos2d::RandomHelper::random_int<int>(BORDER_Y_ORIGIN, BORDER_HEIGHT));
}
