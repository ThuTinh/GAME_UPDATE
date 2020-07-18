#include "Gound.h"
#include "money-effect.h"
#include "Weapon.h"
#include"Simon.h"
#include"Animations.h"
void MoneyEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timeDelay.update();
	if (timeDelay.isTerminated())
	{
		setAlive(false);
	}
	

}

void MoneyEffect::Render()
{
	if (isAlive) {
		animation_set->at(aniIndex)->Render(x, y, frameIndex, DIRECTION_LEFT);
	}
}



MoneyEffect::MoneyEffect()
{
	timeDelay.init(TIMEDELAY);
	animation_set = CAnimationSets::GetInstance()->Get(IDANI);
	setAlive(false);
	setPhysicsEnable(true);
	aniIndex = 0;
}

