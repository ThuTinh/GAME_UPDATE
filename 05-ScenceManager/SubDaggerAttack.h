#pragma once
#include"SubWeaponAttack.h"
#define ANI 30
#define INDEX 2
class SubDaggerAttack : public SubWeaponAttack
{
public:
	SubDaggerAttack();
	~SubDaggerAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
private:

};

