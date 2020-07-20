#pragma once
#include"SubWeaponAttack.h"
#define ANI 66
#define INDEX 2
#define VX_AXE 0.06
#define VY_AXE 0.1
#define AXE_GRAVITY -0.0009
#define TIME_DELAY_AXE 550
class SubFireBombAttack : public SubWeaponAttack
{
public:
	SubFireBombAttack();
	~SubFireBombAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
private:

};

