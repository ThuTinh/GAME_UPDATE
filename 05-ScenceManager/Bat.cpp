#include "Bat.h"
#include"Gound.h"
#include"Simon.h"
#include "Weapon.h"
#include "ScoreBar.h"
#include "Die-affect.h"
#include "BigHeart.h"
#include "Game.h"
void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	switch (state)
	{
	case BAT_STATE_STAND:
		setDx(0);
		setDy(0);
		if (Simon::getInstance()->getX() > getX() && Simon::getInstance()->getX() - getX() < BAT_RUN_DX &&  abs(Simon::getInstance()->getY() - getY() )<80 )
		{
			state = BAT_STATE_FLY;
			setPhysicsEnable(true);
			setVy(BAT_VY);
			setVx(BAT_VX);
			aniIndex = BAT_ACTION_FLY;
			distanceNeedFlyHorizonal = getY() - DISTACE_CHANGE_FLY_HORIZONTAL;
		}
		break;
	case BAT_STATE_FLY:

		if (getY() <= distanceNeedFlyHorizonal) {
			setVx(vx);
			setVy(0);
		}
		if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive && (Weapon::getInstance()->aniIndex == 2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8 || Weapon::getInstance()->aniIndex == 11)) {
				setAlive(false);
				ScoreBar::getInstance()->increaseScore(ENEMY_SCORE);
				DieEffect* dieEffect = new DieEffect();
				CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(dieEffect);
				dieEffect->setX(getMidX());
				dieEffect->setY(getMidY());
				dieEffect->setAlive(true);
				dieEffect->timeDelay.start();
				
		}
		break;
	default:
		break;
	}
	Enemy::Update(dt, coObjects);
	x += dx;
	y += dy;
}

void Bat::Render()
{
	animation_set->at(aniIndex)->Render(x, y, frameIndex, direction);
}

Bat::Bat()
{
	setPhysicsEnable(false);
	setCollitionType(COLLISION_TYPE_ENEMY);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	setPhysicsEnable(true);
	setVx(0.03);
	setPhysicsEnable(false);
	aniIndex = BAT_ACTION_STAND;
	state = BAT_STATE_STAND;

}

Bat::~Bat()
{
}