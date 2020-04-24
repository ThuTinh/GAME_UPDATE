#pragma once
#include "GameObject.h"
class Light : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Light();
	virtual void SetState(int state);
};