#pragma once
#include"SubWeaponAttack.h"
#define ANI 66
#define INDEX 1
#define VX_AXE 0
#define VY_AXE 0.3 
#define AXE_GRAVITY -0.0008
#define TIME_DELAY_AXE 1000
class SubAxeAttack : public SubWeaponAttack
{
public:
	SubAxeAttack();
	~SubAxeAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
private:

};

