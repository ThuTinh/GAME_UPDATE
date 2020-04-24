#include "Gound.h"
#include "Light.h"
#include "Weapon.h"
#include"Simon.h"
void Light::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive()) {
		setAlive(false);
	}
}

void Light::Render()
{
	if (isAlive)
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
}

Light::Light()
{
	setCollitionType(COLLISION_TYPE_MISC);
	setPhysicsEnable(false);
}

void Light::SetState(int state)
{
}
