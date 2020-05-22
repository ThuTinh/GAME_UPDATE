#pragma once
#include"SubWeaponAttack.h"
#define ANI 30
#define INDEX 3
class SubBoomerangAttack : public SubWeaponAttack
{
public:
	SubBoomerangAttack();
	~SubBoomerangAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
private:

};

