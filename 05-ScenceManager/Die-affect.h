#pragma once
#include "GameObject.h"
#include"DelayTime.h"

#define IDANI 50
#define TIMEDELAY 400
class DieEffect : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	
public:
	DelayTime timeDelay;
	DieEffect();
	
};