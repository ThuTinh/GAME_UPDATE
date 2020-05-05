#pragma once
#include"GameObject.h"
class Gate2 : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Gate2();
	~Gate2();

private:

};


