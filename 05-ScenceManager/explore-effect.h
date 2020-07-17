#pragma once
#include "GameObject.h"
#include"DelayTime.h"

#define IDANI_EXPLORE 30
#define INDEX_EXPLORE 8
#define TIMEDELAY 500
class ExploreEffect : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	DelayTime timeDelay;
	ExploreEffect();

};