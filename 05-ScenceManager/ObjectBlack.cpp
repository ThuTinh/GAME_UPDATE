#include "Gound.h"
#include "ObjectBlack.h"
#include "Weapon.h"
#include"Simon.h"
void ObjectBlack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (checkOnlyOne)
		return;
	if (AABBCheck(Weapon::getInstance())) {
		checkOnlyOne = true;
		 Simon::getInstance()->addNumberObjectBlack(1);
		if (getY() <=YTEMP) {
			setY(YRENDER);
		}
		isRender = true;
	}
}

void ObjectBlack::Render()
{
	if (isRender)
	{
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
	}
}

ObjectBlack::ObjectBlack()
{
	setCollitionType(COLLISION_TYPE_MISC);
	setPhysicsEnable(false);
	isRender = false;
	checkOnlyOne = false;
}

void ObjectBlack::SetState(int state)
{
}
