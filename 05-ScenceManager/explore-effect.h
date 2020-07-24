#pragma once
#include "GameObject.h"
#include"DelayTime.h"

#define IDANI_EXPLORE 46
#define INDEX_EXPLORE 0
#define TIMEDELAY 500
class ExploreEffect : public CGameObject
{
public:
	DelayTime timeDelay;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	ExploreEffect();

};