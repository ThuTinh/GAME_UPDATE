#pragma once
#include "GameObject.h"
class Ground : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Ground();
	virtual void SetState(int state);
};