#include "Gound.h"
#include "Die-affect.h"
#include "Weapon.h"
#include"Simon.h"
#include"Animations.h"
void DieEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timeDelay.update();
	if (timeDelay.isTerminated())
	{
		setAlive(false);
	}
}

void DieEffect::Render()
{
	if (isAlive) {
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
	}
}

DieEffect::DieEffect()
{
	timeDelay.init(TIMEDELAY);
	animation_set = CAnimationSets::GetInstance()->Get(IDANI);
	setAlive(false);
}

