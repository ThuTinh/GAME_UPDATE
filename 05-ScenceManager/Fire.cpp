#include "Gound.h"
#include "Fire.h"
#include "Weapon.h"
#include"Simon.h"
#include "Die-affect.h"
#include "Game.h"
void Fire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && (Weapon::getInstance()->aniIndex == 2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8 || Weapon::getInstance()->aniIndex == 11 || Weapon::getInstance()->aniIndex == 14 || Weapon::getInstance()->aniIndex == 17)) {
		setAlive(false);
		makeDieEffect();
	}
}

void Fire::Render()
{
	if(isAlive)
		animation_set->at(0)->Render(x, y,frameIndex ,DIRECTION_LEFT);
}

Fire::Fire()
{
	setCollitionType(COLLISION_TYPE_MISC);
	setPhysicsEnable(false);
}

void Fire::SetState(int state)
{
}
