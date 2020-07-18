#pragma once
#include"GameObject.h"
#include "DelayTime.h"
#include "GameTime.h"
#define VX 0.125
#define TIME_DELAY 3000
class SubWeaponAttack : public CGameObject
{
public:
	SubWeaponAttack();
	~SubWeaponAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void setDirectionFollowPlayer();
	DelayTime timeDelay;
	DelayTime timeCheckSimon;
private:

};

