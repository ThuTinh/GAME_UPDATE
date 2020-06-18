#pragma once
#include"SubWeaponAttack.h"
#define ANI 66
#define INDEX 0
class SubBoomerangAttack : public SubWeaponAttack
{
public:
	SubBoomerangAttack();
	~SubBoomerangAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
private:

};

