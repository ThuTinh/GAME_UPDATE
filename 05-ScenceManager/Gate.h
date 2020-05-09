#pragma once
#include"GameObject.h"
class Gate : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Gate();
	~Gate();

private:

};


