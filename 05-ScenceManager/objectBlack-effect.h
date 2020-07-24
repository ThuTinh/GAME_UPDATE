#pragma once
#include "GameObject.h"
#include"DelayTime.h"
#define IDANI 70
#define TIMEDELAY 2000
#define GRAVITY_EFFECT -0.0002
class ObjectBlackEffect : public CGameObject
{
public:
	DelayTime timeDelay;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	ObjectBlackEffect();

};