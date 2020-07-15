#include "Gound.h"
#include "money-effect.h"
#include "Weapon.h"
#include"Simon.h"
#include"Animations.h"
void MoneyEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timeDelay.update();
	CGameObject::Update(dt, coObjects);
	setX(getX() + dx);
	setY(getY() + dy);
	if (timeDelay.isTerminated())
	{
		setAlive(false);
	}
	vy += GRAVITY_EFFECT * dt;

}

void MoneyEffect::Render()
{
	if (isAlive) {
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
	}
}



MoneyEffect::MoneyEffect()
{
	timeDelay.init(TIMEDELAY);
	animation_set = CAnimationSets::GetInstance()->Get(IDANI);
	setAlive(false);
	setPhysicsEnable(true);
}

