#pragma once
#include "GameObject.h"
class Fire : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Fire() ;
	virtual void SetState(int state);
};