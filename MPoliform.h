#pragma once
#include "PreDefines.h"
#include "Motif.h"
#include "Emitter.h"
#include "AI.h"


class MPoliform : public Motif
{
public:

	MPoliform();

	virtual void Update() override;

	~MPoliform();

private:
	
	Emitter* emitter_1;
	std::unique_ptr<AI> behavior;

	void CreateEmitter_1();
	cocos2d::Vec2 GetRandomPositionFromBorderBox();
};

