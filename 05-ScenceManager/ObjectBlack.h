#pragma once
#include "GameObject.h"
//map height 384
#define YRENDER 95
#define YTEMP 94
class ObjectBlack : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void restorePosition() override;
	bool isRender;
	bool checkOnlyOne;

public:
	ObjectBlack();
	virtual void SetState(int state);
	void makeEfect();

};