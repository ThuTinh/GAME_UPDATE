#include "Gound.h"
#include "objectBlack-effect.h"
#include "Weapon.h"
#include"Simon.h"
#include"Animations.h"
void ObjectBlackEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void ObjectBlackEffect::Render()
{
	if (isAlive) {
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
	}
}

ObjectBlackEffect::ObjectBlackEffect()
{
	timeDelay.init(TIMEDELAY);
	animation_set = CAnimationSets::GetInstance()->Get(IDANI);
	setAlive(false);
	setPhysicsEnable(true);
}

