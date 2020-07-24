#pragma once
#include"SubWeaponAttack.h"
class SubStopWatchAttack : public SubWeaponAttack
{
public:
	SubStopWatchAttack();
	~SubStopWatchAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
private:

};

