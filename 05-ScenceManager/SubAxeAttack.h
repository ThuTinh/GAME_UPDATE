#pragma once
#include"SubWeaponAttack.h"
#define ANI 30
#define INDEX 4
class SubAxeAttack : public SubWeaponAttack
{
public:
	SubAxeAttack();
	~SubAxeAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
private:

};

