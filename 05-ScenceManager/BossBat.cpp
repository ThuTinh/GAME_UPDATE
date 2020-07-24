#include "BossBat.h"
#include "Camera.h"
#include"Die-affect.h"
#include "Weapon.h"
#include"Game.h"
#include "SubWeaponAttack.h"
#include"PlayScence.h"
#include "hit-effect.h"
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
			int distance = player->getX() - getX();
			if (distance > boss_distance_activ)
			{
				aniIndex = BOSS_ACTION_ACTIV;
				setBossState(BOSS_STATE_WAIT);
				float tempX = Simon::getInstance()->getX();
				float tempY = Simon::getInstance()->getY();
				dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->setCurentSpace(1);
				Simon::getInstance()->setX(tempX);
				Simon::getInstance()->setY(tempY);
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
			//Boss vượt qua camera bên trái thì tính lại vx, vy cho boss
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
			//Boss vượt qua camera bên phải thì tính lại vx, vy cho boss
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
				setBossState(BOSS_STATE_MOVE_SLOW);
				DWORD moveSlowDelayTime = getRandom(boss_move_slow_time_min, boss_move_slow_time_max);
				moveSlowDelay.start(moveSlowDelayTime);
				calculateOtherPoint();
				setVx(0);
				setVy(0);
				if (xDes < getX())
				{
					setDx(-1.5);
				}
				else
				{
					setDx(1.5);
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
		xDes = camera->getRight() ;
	}

	int yMin = player->getMidY() - 60 ;

	int yMax = player->getMidY();

	yDes = getRandom(yMin, yMax);
}

void BossBat::checkWithSimon()
{
	hurtDelay.update();
	if (CGame::GetInstance()->GetCurrentScene()->getAddtionalObject().size() > 0) {
		vector<LPGAMEOBJECT> listObject = CGame::GetInstance()->GetCurrentScene()->getAddtionalObject();
		for (size_t i = 0; i < listObject.size(); i++)
		{
			if (dynamic_cast<SubWeaponAttack*>(listObject[i]) && listObject[i]->isAlive) {
				if (AABBCheck(listObject[i])) {
					if (ScoreBar::getInstance()->getBossHealth() > 1)
					{
						hurtDelay.start();
						makeHitEffect();
					}
					else
					{
						makeDieEffect();
						return;
					}
				}
			}
		}
	}
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive && (Weapon::getInstance()->aniIndex == 2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8 || Weapon::getInstance()->aniIndex == 11 || Weapon::getInstance()->aniIndex == 14 || Weapon::getInstance()->aniIndex == 17)) {
		hurtDelay.start();
		makeHitEffect();
		if (ScoreBar::getInstance()->getBossHealth() == 1)
		{
			makeDieEffect();
			return;
		}
	}
	if (AABBCheck(Simon::getInstance())) {
		if (Simon::getInstance()->state != SIMON_STATE_ON_STAIR) {
			if (!Simon::getInstance()->isDie()) {
				Simon::getInstance()->setHurt(getDirection(), getX());
			}
		}
		else
		{
			Simon::getInstance()->setHurtInStair();
		}
	}
	
	if (hurtDelay.isTerminated()) {
		if (ScoreBar::getInstance()->getBossHealth()  > 2)
		{
			ScoreBar::getInstance()->increaseBossHealth(-2);
		}
		else
		{
			makeDieEffect();
			return;
		}
	}
}

void BossBat::onDecreaseHealth()
{
	ScoreBar::getInstance()->increaseBossHealth(-16);
}

void BossBat::makeDieEffect()
{
	ScoreBar::getInstance()->increaseBossHealth(-2);
	DieEffect* dieEffect = new DieEffect();
	DieEffect* dieEffect1 = new DieEffect();
	CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(dieEffect);
	dieEffect->setX(getMidX());
	dieEffect->setY(getMidY());
	dieEffect->setAlive(true);
	dieEffect->timeDelay.start();
	CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(dieEffect1);
	dieEffect1->setX(getMidX()+10);
	dieEffect1->setY(getMidY());
	dieEffect1->setAlive(true);
	dieEffect1->timeDelay.start();
	setAlive(false);
	Simon::getInstance()->isWin = true;
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
	//boss vượt qua bên trái/phải camera
	if ((getX() + getDx() < camera->getleft() && getDx() < 0) || (getRight() + getDx() > camera->getRight() && getDx() > 0))
	{
		setDx(-getDx());
	}
	//Boss vượt qua phía trên/dưới camera
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
	waitDelay.init(Boss_time_wait);
	setPhysicsEnable(false);
	aniIndex = 0;
	setAlive(true);
	hurtDelay.init(40);
}

BossBat::~BossBat()
{
	
}
