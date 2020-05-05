#pragma once
#include"GameObject.h"
class GateStair2 : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	GateStair2();
	~GateStair2();

private:

};


