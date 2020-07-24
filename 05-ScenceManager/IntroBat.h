#pragma once
#include "GameObject.h"
class IntroBat : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	IntroBat();
};