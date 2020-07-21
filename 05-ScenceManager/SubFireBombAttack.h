#pragma once
#include"SubWeaponAttack.h"
#define ANI 66
#define INDEX 2
#define VX_AXE 0.07
#define VY_AXE 0.15
#define AXE_GRAVITY -0.0008
#define TIME_DELAY_FRIE_BOOM 550
class SubFireBombAttack : public SubWeaponAttack
{
public:
	SubFireBombAttack();
	~SubFireBombAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void makeExploreEffect(LPGAMEOBJECT obj);
private:

};

