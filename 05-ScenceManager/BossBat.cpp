#include "BossBat.h"
#include "Camera.h"
#include"Die-affect.h"
#include "Weapon.h"
#include"Game.h"
#include "SubWeaponAttack.h"
#include"PlayScence.h"
#define MAX(a,b) (a>b? a : b)
#define MIN(a,b) (a<b? a : b)
extern int getRandom(int start, int end);

void BossBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float vx2 = 0, vy2 = 0;
	waitDelay.update();
	moveFastDelay.update();
	moveSlowDelay.update();
	checkWithSimon();
	pauseAnimation = false;
	if (!CGame::GetInstance()->GetCurrentScene()->getStopUpdate()) {
		switch (bossState)
		{
		case BOSS_STATE_INVISIBLE:
		{
			//dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->setCurentSpace(1);
			int distance = player->getX() - getX();
			if (distance > boss_distance_activ)
			{

				aniIndex = BOSS_ACTION_ACTIV;
				setBossState(BOSS_STATE_WAIT);
				calculateOtherPoint();
				if (xDes < getX())
				{
					vx2 = -vampire_bat_fast_momen;
				}
				else
				{
					vx2 = vampire_bat_fast_momen;
				}
				vy2 = (vx2 * (yDes - getY()) / (xDes - getX()));
				waitDelay.start();
			}
			break;
		}
		case BOSS_STATE_WAIT:
			setDx(0);
			setVx(0);
			setDy(0);
			setVy(0);
			if (waitDelay.isTerminated())
			{
				setBossState(BOSS_STATE_MOVE_FAST);
				DWORD moveFastDelayTime = getRandom(boss_move_fast_time_min, boss_move_fast_time_max);
				moveFastDelay.start(moveFastDelayTime);
				calculateOtherPoint();
				if (xDes < getX())
				{
					vx2 = -vampire_bat_fast_momen;
				}
				else
				{
					vx2 = vampire_bat_fast_momen;
				}
				vy2 = (vx2 * (yDes - getY()) / (xDes - getX()));
				setVx(vx2);
				setVy(vy2);
			}
			break;
		case BOSS_STATE_MOVE_FAST:
		{
			auto camera = Camera::getInstance();

			if (getDx() < 0 && camera->getleft() > getX() + getDx())
			{
				calculateOtherPoint();
				if (xDes < getX())
				{
					vx2 = -vampire_bat_fast_momen;
				}
				else
				{
					vx2 = vampire_bat_fast_momen;
				}
				vy2 = (vx2 * (yDes - getY()) / (xDes - getX()));
				setVx(vx2);
				setVy(vy2);
			}

			if (getDx() > 0 && camera->getRight() < getRight() + getDx())
			{
				calculateOtherPoint();
				if (xDes < getX())
				{
					vx2 = -vampire_bat_fast_momen;
				}
				else
				{
					vx2 = vampire_bat_fast_momen;
				}
				vy2 = (vx2 * (yDes - getY()) / (xDes - getX()));
				setVx(vx2);
				setVy(vy2);
			}

			if (moveFastDelay.isTerminated())
			{
				waitDelay.start();
				setBossState(BOSS_STATE_MOVE_SLOW);
				DWORD moveSlowDelayTime = getRandom(boss_move_slow_time_min, boss_move_slow_time_max);
				moveSlowDelay.start(moveSlowDelayTime);
				calculateOtherPoint();
				setVx(0);
				setVy(0);
				if (xDes < getX())
				{
					setDx(-1);
				}
				else
				{
					setDx(1);
				}
				setDy(-(getDx() * (yDes - getY()) / (xDes - getX())));
				return;
			}

			preventGoOutsideCamera();
			CGameObject::Update(dt, coObjects);
			break;
		}
		case BOSS_STATE_MOVE_SLOW:
			if (moveSlowDelay.isTerminated())
			{
				setBossState(BOSS_STATE_WAIT);
				waitDelay.start();
			}
			preventGoOutsideCamera();
			break;
		default:
			break;
		}
		setX(getX() + getDx());
		setY(getY() + getDy());
	}
	 else
	{
	pauseAnimation = true;
	}
	

}

void BossBat::Render()
{
	if (isAlive)
		animation_set->at(aniIndex)->Render(x, y, frameIndex, direction, pauseAnimation);
}

void BossBat::setBossState(BOSS_STATE bossState)
{
	this->bossState = bossState;
}

void BossBat::calculateOtherPoint()
{
	auto camera = Camera::getInstance();
	if (getMidX() > player->getMidX() && getX() - camera->getX() > 30)
	{
		xDes = camera->getleft();
	}
	else
	{
		xDes = camera->getRight();
	}

	int yMin = player->getMidY() - 60;

	int yMax = player->getMidY();

	yDes = getRandom(yMin, yMax);
}

void BossBat::checkWithSimon()
{
	hurtDelay.update();
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive && (Weapon::getInstance()->aniIndex == 2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8 || Weapon::getInstance()->aniIndex == 11 || Weapon::getInstance()->aniIndex == 14 || Weapon::getInstance()->aniIndex == 17)) {
		hurtDelay.start();
		if (ScoreBar::getInstance()->getBossHealth() == 1)
		{
			makeEffectDie();
			return;
		}
	}
	if (AABBCheck(Simon::getInstance()) && Simon::getInstance()->state != SIMON_STATE_ON_STAIR) {
		if (!Simon::getInstance()->isDie()) {
			Simon::getInstance()->setHurt(getDirection(), getX());
		}
	}
	if (CGame::GetInstance()->GetCurrentScene()->getAddtionalObject().size() > 0) {
		vector<LPGAMEOBJECT> listObject = CGame::GetInstance()->GetCurrentScene()->getAddtionalObject();
		for (size_t i = 0; i < listObject.size(); i++)
		{
			if (dynamic_cast<SubWeaponAttack*>(listObject[i]) && listObject[i]->isAlive) {
				if (AABBCheck(listObject[i])) {
					if (ScoreBar::getInstance()->getBossHealth() > 1)
					{
						
						hurtDelay.start();
					}
					else
					{
						makeEffectDie();
						return;
					}
				}
			}
		}
	}
	if (hurtDelay.isTerminated()) {
		if (ScoreBar::getInstance()->getBossHealth()  > 1)
		{
			ScoreBar::getInstance()->increaseBossHealth(-1);

		}
		else
		{
			makeEffectDie();
			return;
		}
	}
}

void BossBat::onDecreaseHealth()
{
	ScoreBar::getInstance()->increaseBossHealth(-16);
}

void BossBat::makeEffectDie()
{
	ScoreBar::getInstance()->increaseBossHealth(-1);
	DieEffect* dieEffect = new DieEffect();
	CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(dieEffect);
	dieEffect->setX(getMidX());
	dieEffect->setY(getMidY());
	dieEffect->setAlive(true);
	dieEffect->timeDelay.start();
	setAlive(false);
}

void BossBat::restore()
{
	aniIndex = BOSS_ACTION_WAIT;
	setBossState(BOSS_STATE_INVISIBLE);
	setVx(0);
	setDx(0);
	setVy(0);
	setDy(0);
}

void BossBat::preventGoOutsideCamera()
{
	auto camera = Camera::getInstance();

	if ((getX() + getDx() < camera->getleft() && getDx() < 0) || (getRight() + getDx() > camera->getRight() && getDx() > 0))
	{
		setDx(-getDx());
	}

	if ((getY() + getDy() > camera->getTop() - 48 && getDy() > 0)
		|| (getBottom() + getDy() < camera->getBottom() + 32 && getDy() < 0))
	{
		setDy(-getDy());
	}
}

BossBat::BossBat()
{
	player = Simon::getInstance();
	setDirection(DIRECTION_LEFT);
	waitDelay.init(BOSS_TIME_WAITE);
	setPhysicsEnable(false);
	aniIndex = 0;
	setAlive(true);
	hurtDelay.init(10);
}

BossBat::~BossBat()
{
	
}
