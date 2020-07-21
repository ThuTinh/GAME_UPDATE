#pragma once
#include "GameObject.h"
#include"DelayTime.h"

#define IDANI 45
#define TIMEDELAY 400
class HitEffect : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	DelayTime timeDelay;
	HitEffect();

};