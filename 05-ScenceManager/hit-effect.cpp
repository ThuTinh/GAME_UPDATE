#include "Gound.h"
#include "hit-effect.h"
#include "Weapon.h"
#include"Simon.h"
#include"Animations.h"
void HitEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timeDelay.update();
	if (timeDelay.isTerminated())
	{
		setAlive(false);
	}
}

void HitEffect::Render()
{
	if (isAlive) {
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
	}
}

HitEffect::HitEffect()
{
	timeDelay.init(TIMEDELAY);
	animation_set = CAnimationSets::GetInstance()->Get(IDANI);
	setAlive(false);
}

