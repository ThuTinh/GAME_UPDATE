#pragma once
#pragma once
#include "Gound.h"
#define MAX_X 90
#define MIN_X	30
#define Vx 0.02
class GiaDo : public Ground
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	int nx;
	GiaDo();
};