

#pragma once
#include "PreDefines.h"
#include "Motif.h"
#include "Emitter.h"
#include "AI.h"


class Motif_WhiteWall : public Motif
{
public:
	Motif_WhiteWall();

	virtual void TurnOnAllEmitters() override;
	virtual void TurnOffAllEmitters() override;
	virtual void Init() override;

	~Motif_WhiteWall();

private:
	
	Emitter* Emitter_;

	void CreateEmitter();
};

