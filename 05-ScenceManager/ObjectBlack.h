#pragma once
#include "GameObject.h"
class ObjectBlack : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	ObjectBlack();
	virtual void SetState(int state);
};