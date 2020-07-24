#pragma once
#include"GameObject.h"
#include "DelayTime.h"
class GateIntro : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	DelayTime delayWait;
	bool CheckOnlyOne;
	virtual void Render();
	GateIntro();
	~GateIntro();

private:

};


