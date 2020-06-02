#include "SubWeaponAttack.h"
#include"Simon.h"
#include"ScoreBar.h"
void SubWeaponAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timeDelay.update();
	if (timeDelay.isTerminated())
	{
		setAlive(false);
	}
	CGameObject::Update(dt, coObjects);
	setDirectionFollowPlayer();
	setX(( direction)*getDx() + getX());
	
}

void SubWeaponAttack::Render()
{
}

void SubWeaponAttack::setDirectionFollowPlayer()
{
	if (Simon::getInstance()->getDirection() == DIRECTION_LEFT)
		setDirection(DIRECTION_LEFT);

	else
	{
		setDirection(DIRECTION_RIGHT);

	}
}

SubWeaponAttack::SubWeaponAttack()
{
	setVy(0);
	setVx(VX);
	timeDelay.init(TIME_DELAY);
	
}

SubWeaponAttack::~SubWeaponAttack()
{
}