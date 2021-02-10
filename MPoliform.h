#pragma once
#include "Motif.h"
#include "Emitter.h"



class MPoliform : public Motif
{
public:

	MPoliform();

	virtual void Update() override;

	~MPoliform();

private:
	
	Emitter* emitter_1;

	void CreateEmitter_1();
};

