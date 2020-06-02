#include "BossBat.h"

void BossBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void BossBat::Render()
{
	if (isAlive)
		animation_set->at(aniIndex)->Render(x, y, frameIndex, direction);
}

BossBat::BossBat()
{
	setPhysicsEnable(false);
	aniIndex = 0;
	setAlive(true);

}

BossBat::~BossBat()
{
}
