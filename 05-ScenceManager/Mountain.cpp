#include "Gound.h"
#include "Mountain.h"
void Mountain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
}

void Mountain::Render()
{
	if (frameIndex == 14) {
		checkLastAni = true;
	}
	if (checkLastAni) {
		animation_set->at(0)->setCurrentFrame(12);
	}
	animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
	checkLastAni = false;
}

Mountain::Mountain()
{
	setPhysicsEnable(false);
	checkLastAni = false;
}

void Mountain::SetState(int state)
{
}
