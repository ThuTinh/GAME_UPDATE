#pragma once
#include "GameObject.h"
class Mountain : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	bool checkLastAni;
	Mountain();
};