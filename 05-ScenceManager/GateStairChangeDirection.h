#pragma once
#include"GameObject.h"
class GateStairChangeDirection : public CGameObject
{
	bool checkOnlyOne;

public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	GateStairChangeDirection();
	~GateStairChangeDirection();

private:

};


