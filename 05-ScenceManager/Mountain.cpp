#include "Gound.h"
#include "Mountain.h"
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
