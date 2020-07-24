#include "SubWeaponAttack.h"
#include"Simon.h"
#include"ScoreBar.h"
void SubWeaponAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timeDelay.update();
	timeCheckSimon.update();
	if (timeDelay.isTerminated())
	{
		Simon::getInstance()->canMakeSub = true;
		setAlive(false);
	}
	CGameObject::Update(dt, coObjects);
	setX(getDx() + getX());
	
}

void SubWeaponAttack::Render()
{
}

void SubWeaponAttack::setDirectionFollowPlayer()
{
	if (Simon::getInstance()->getDirection() == DIRECTION_LEFT) {
		setDirection(DIRECTION_LEFT);
		setVx(-VX);
	}
	else
	{
		setDirection(DIRECTION_RIGHT);
		setVx(VX);
	}
}

SubWeaponAttack::SubWeaponAttack()
{
	setVy(0);
	timeDelay.init(TIME_DELAY);
	timeCheckSimon.init(100);
	setDirectionFollowPlayer();
	
}

SubWeaponAttack::~SubWeaponAttack()
{
}