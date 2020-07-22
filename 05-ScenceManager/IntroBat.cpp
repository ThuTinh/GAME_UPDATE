#include "Gound.h"
#include "IntroBat.h"
#include "Weapon.h"
#include"Simon.h"
#include "Die-affect.h"
#include "Game.h"
void IntroBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	setX(getX() + getDirection() * 0.2);
	setY(getY() + getDirection() * 0.05); 
}

void IntroBat::Render()
{
	if (isAlive)
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
}

IntroBat::IntroBat()
{
	setPhysicsEnable(false);
	
}

void IntroBat::SetState(int state)
{
}
