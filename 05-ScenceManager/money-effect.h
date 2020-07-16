#pragma once
#include "GameObject.h"
#include"DelayTime.h"

#define IDANI 44
#define TIMEDELAY 1000
class MoneyEffect : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	DelayTime timeDelay;
	MoneyEffect();

};