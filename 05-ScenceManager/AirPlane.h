#pragma once
#include "GameObject.h"
class AirPlane : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	AirPlane();
};