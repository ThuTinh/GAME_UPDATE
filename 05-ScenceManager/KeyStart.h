#pragma once
#include "GameObject.h"
#include "DelayTime.h"
#include "GameTime.h"
class KeyStart : public CGameObject
{
	static KeyStart* instance;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	DelayTime delayAni;
	GameTime timeAni;
	bool isRender;

	KeyStart();
};