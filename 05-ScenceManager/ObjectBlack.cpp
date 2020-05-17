#include "Gound.h"
#include "ObjectBlack.h"
#include "Weapon.h"
#include"Simon.h"
void ObjectBlack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
}

void ObjectBlack::Render()
{
	if (isAlive)
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
}

ObjectBlack::ObjectBlack()
{
	setCollitionType(COLLISION_TYPE_MISC);
	setPhysicsEnable(false);
	setAlive(true);
}

void ObjectBlack::SetState(int state)
{
}
