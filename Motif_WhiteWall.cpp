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

#include "Motif_WhiteWall.h"

void Motif_WhiteWall::TurnOnAllEmitters()
{
	Emitter_->Play();
}

void Motif_WhiteWall::TurnOffAllEmitters()
{
	Emitter_->Stop();
}

Motif_WhiteWall::Motif_WhiteWall()
{
	Position = GetRandomPositionFromBorderBox(
		cocos2d::Vec4(
			BORDER_X_ORIGIN-100, BORDER_Y_ORIGIN-100,
			BORDER_HEIGHT+100, BORDER_WIDTH+100));

	RefreshRate = 0.3;
	CreateEmitter();
};
	
	

Motif_WhiteWall::~Motif_WhiteWall()
{
	Emitter_->Destroy();
}

void Motif_WhiteWall::CreateEmitter()
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

	vertiesList.push_back(Triangle);
	vertiesList.push_back(Triangle);
	vertiesList.push_back(Triangle);
	vertiesList.push_back(Triangle);

	std::array<ParticleSettings<2>, 6> prtl_s;
	prtl_s[0].BeginBorderColor = cocos2d::Color4B::ORANGE;
	prtl_s[0].BeginFillColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[0].BeginBorderWith = { 1.2, 1.2 };
	prtl_s[0].BeginRotation = { 45,45 };
	prtl_s[0].BeginScale = { 1,1.1 };
	prtl_s[0].FadeOutDuration = { 0.6,0.9 };
	prtl_s[0].LifeTime = { 1,1 };
	prtl_s[0].ZOrderIndex = {12,12};

	prtl_s[1].BeginBorderColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[1].BeginFillColor = cocos2d::Color4B::WHITE;
	prtl_s[1].BeginBorderWith = { 0,0 };
	prtl_s[1].BeginRotation = { 0,0 };
	prtl_s[1].BeginScale = { 1,1.1 };
	prtl_s[1].FadeOutDuration = { 0.6,0.9 };
	prtl_s[1].LifeTime = { 1,1 };
	prtl_s[1].ZOrderIndex = { 12,12 };

	prtl_s[2].BeginBorderColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[2].BeginFillColor = cocos2d::Color4B::WHITE;
	prtl_s[2].BeginBorderWith = { 0,0 };
	prtl_s[2].BeginRotation = { 45,45 };
	prtl_s[2].BeginScale = { 1,1.2 };
	prtl_s[2].FadeOutDuration = { 0.6,0.9 };
	prtl_s[2].LifeTime = { 1,1 };
	prtl_s[2].ZOrderIndex = { 12,12 };

	prtl_s[3].BeginBorderColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[3].BeginFillColor = cocos2d::Color4B::WHITE;
	prtl_s[3].BeginBorderWith = { 0,0 };
	prtl_s[3].BeginRotation = { -45,-45 };
	prtl_s[3].BeginScale = { 1,1.1 };
	prtl_s[3].FadeOutDuration = { 0.6,0.9 };
	prtl_s[3].LifeTime = { 1,1 };
	prtl_s[3].ZOrderIndex = { 12,12 };
	
	prtl_s[4].BeginBorderColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[4].BeginFillColor = cocos2d::Color4B::WHITE;
	prtl_s[4].BeginBorderWith = { 0,0 };
	prtl_s[4].BeginRotation = { -180,-180 };
	prtl_s[4].BeginScale = { 1,1.2 };
	prtl_s[4].FadeOutDuration = { 0.6,0.9 };
	prtl_s[4].LifeTime = { 1,1 };
	prtl_s[4].ZOrderIndex = { 12,12 };

	prtl_s[5].BeginBorderColor = cocos2d::Color4B::ORANGE;
	prtl_s[5].BeginFillColor = cocos2d::Color4B(0, 0, 0, 0);
	prtl_s[5].BeginBorderWith = { 1.2, 1.2 };
	prtl_s[5].BeginRotation = { 0,0 };
	prtl_s[5].BeginScale = { 1,1.1 };
	prtl_s[5].FadeOutDuration = { 0.6,0.9 };
	prtl_s[5].LifeTime = { 1,1 };
	prtl_s[5].ZOrderIndex = { 12,12 };
	

	EmitterSettings emitter_s;
	emitter_s.ParticleSettingsScope.push_back(prtl_s[1]);
	emitter_s.ParticleSettingsScope.push_back(prtl_s[2]);
	emitter_s.ParticleSettingsScope.push_back(prtl_s[3]);
	emitter_s.ParticleSettingsScope.push_back(prtl_s[4]);
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
		ParticleAction{ [this]()->cocos2d::Action* {return cocos2d::MoveBy::create(2,cocos2d::Vec2(-100,100)); }, ProcStatus::Begin });
	emitter_s.ActionSequence.push_back(
		ParticleAction{ [this]()->cocos2d::Action* {return cocos2d::ScaleBy::create(2,1.5); }, ProcStatus::End });
	emitter_s.ActionSequence.push_back(
		ParticleAction{ [this]()->cocos2d::Action* {return cocos2d::FadeOut::create(1); }, ProcStatus::End });
	Emitter_ = new Emitter(&emitter_s, vertiesList);
	Emitter_->Init();
}

cocos2d::Vec2 Motif_WhiteWall::GetRandomPositionFromBorderBox(cocos2d::Vec4 &BorderBox)
{
	return cocos2d::Vec2(
		cocos2d::RandomHelper::random_int<int>(BorderBox.x, BorderBox.w),
		cocos2d::RandomHelper::random_int<int>(BorderBox.y, BorderBox.z));
}
