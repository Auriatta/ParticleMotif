#include "Motif_PlusShape.h"

Motif_PlusShape::Motif_PlusShape()
{
	RefreshRate = 0.3;
	CreateEmitter();
}

void Motif_PlusShape::TurnOnAllEmitters()
{
	Emitter_->Play();
}

void Motif_PlusShape::TurnOffAllEmitters()
{
	Emitter_->Stop();
}

Motif_PlusShape::~Motif_PlusShape()
{
	Emitter_->Destroy();
}

void Motif_PlusShape::CreateEmitter()
{
	std::vector < std::vector<cocos2d::Vec2>> vertiesList;

	const std::vector<cocos2d::Vec2> Rectangle = {
		cocos2d::Vec2(30, 0),
	cocos2d::Vec2(30, -30),
	cocos2d::Vec2(0, -30),
	cocos2d::Vec2(0, 0)
	};
	

	vertiesList.push_back(Rectangle);
	vertiesList.push_back(Rectangle);

	std::array<ParticleSettings<2>, 2> prtl_s;
	prtl_s[0].BeginBorderColor = cocos2d::Color4B::ORANGE;
	prtl_s[0].BeginFillColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[0].BeginBorderWith = { 1.2, 1.2 };
	prtl_s[0].BeginRotation = { 45,45 };
	prtl_s[0].BeginScale = { 1,1.1 };
	prtl_s[0].FadeOutDuration = { 0.6,0.9 };
	prtl_s[0].LifeTime = { 1,1 };
	prtl_s[0].ZOrderIndex = { 10,10 };

	prtl_s[1].BeginBorderColor = cocos2d::Color4B::ORANGE;
	prtl_s[1].BeginFillColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[1].BeginBorderWith = { 1.2, 1.2 };
	prtl_s[1].BeginRotation = { 0,0 };
	prtl_s[1].BeginScale = { 1,1.1 };
	prtl_s[1].FadeOutDuration = { 0.6,0.9 };
	prtl_s[1].LifeTime = { 1,1 };
	prtl_s[1].ZOrderIndex = { 10,10 };


	EmitterSettings emitter_s;
	emitter_s.ParticleSettingsScope.push_back(prtl_s[0]);
	emitter_s.ParticleSettingsScope.push_back(prtl_s[1]);
	emitter_s.ParticleSpawnBoundriesOffset = cocos2d::Vec4(-100, -125, 125, 100);
	emitter_s.Position = Position;
	emitter_s.UpdateRate = 1;
	emitter_s.RandParticleSettings = true;
	emitter_s.RandVertiesShapes = true;
	emitter_s.ShuffleParticleSettingsElements = false;
	emitter_s.RandGlobalIndex = true;
	emitter_s.ActionSequence.push_back(
		ParticleAction{ [this]()->cocos2d::Action* {return cocos2d::FadeIn::create(1); }, ProcStatus::Begin });
	emitter_s.ActionSequence.push_back(
		ParticleAction{ [this]()->cocos2d::Action* {return cocos2d::MoveBy::create(2,cocos2d::Vec2(0,100)); }, ProcStatus::Begin });
	emitter_s.ActionSequence.push_back(
		ParticleAction{ [this]()->cocos2d::Action* {return cocos2d::ScaleBy::create(2,1.5); }, ProcStatus::End });
	emitter_s.ActionSequence.push_back(
		ParticleAction{ [this]()->cocos2d::Action* {return cocos2d::FadeOut::create(1); }, ProcStatus::End });
	Emitter_ = new Emitter(&emitter_s, vertiesList);
	Emitter_->Init();
}
