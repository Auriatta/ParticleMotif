#pragma once
#include "PreDefines.h"
#include"Motif.h"
#include"Emitter.h"

class Motif_PlusShape : public Motif
{
public:


	Motif_PlusShape();

	virtual void TurnOnAllEmitters();
	virtual void TurnOffAllEmitters();


	~Motif_PlusShape();

private:

	Emitter* Emitter_;
	cocos2d::Vec2 Position;

	void CreateEmitter();

};

