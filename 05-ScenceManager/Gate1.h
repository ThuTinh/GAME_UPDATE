#pragma once
#include"GameObject.h"
class Gate1 : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Gate1();
	~Gate1();

private:

};


