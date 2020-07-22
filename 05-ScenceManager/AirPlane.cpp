#include "Gound.h"
#include "AirPlane.h"
#include "Weapon.h"
#include"Simon.h"
#include "Die-affect.h"
#include "Game.h"
void AirPlane::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	setX(getX() - 0.2);
}

void AirPlane::Render()
{
	if (isAlive)
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
}

AirPlane::AirPlane()
{
	setPhysicsEnable(false);
}

void AirPlane::SetState(int state)
{
}
