#include "Gound.h"
#include "Fire.h"
#include "Weapon.h"
#include"Simon.h"
void Fire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive()) {
		setAlive(false);
	}
}

void Fire::Render()
{
	if(isAlive)
		animation_set->at(0)->Render(x, y,frameIndex ,DIRECTION_LEFT);
}

Fire::Fire()
{
}

void Fire::SetState(int state)
{
}
