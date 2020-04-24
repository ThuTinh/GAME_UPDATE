#pragma once
#include"GameObject.h"
class GateStair1 : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	GateStair1();
	~GateStair1();

private:

};


