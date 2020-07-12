#pragma once
#include"SubWeaponAttack.h"
#define ANI 66
#define INDEX 3
#define VX_AXE 0.0001
#define VY_AXE 0.08
#define AXE_GRAVITY -0.0005
#define TIME_DELAY_AXE 550
class SubStopWatchAttack : public SubWeaponAttack
{
public:
	SubStopWatchAttack();
	~SubStopWatchAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
private:

};

