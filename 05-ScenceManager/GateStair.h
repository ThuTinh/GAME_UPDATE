#pragma once
#include"GameObject.h"
class GateStair : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	GateStair();
	~GateStair();

private:

};


