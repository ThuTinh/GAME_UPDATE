#include "Gound.h"
#include "Mountain.h"
#include "Weapon.h"
#include"Simon.h"
#include "Die-affect.h"
#include "Game.h"
void Mountain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
}

void Mountain::Render()
{
	animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
}

Mountain::Mountain()
{
	setPhysicsEnable(false);
}

void Mountain::SetState(int state)
{
}
