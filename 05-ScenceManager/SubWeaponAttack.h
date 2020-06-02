#pragma once
#include"GameObject.h"
#include "DelayTime.h"
#define VX 0.5
#define TIME_DELAY 4000
class SubWeaponAttack : public CGameObject
{
public:
	SubWeaponAttack();
	~SubWeaponAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void setDirectionFollowPlayer();
	DelayTime timeDelay;
private:

};

