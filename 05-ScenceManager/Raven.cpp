﻿#include "Raven.h"
#include"Gound.h"
#include "Game.h"
#include "Weapon.h"
#include "ScoreBar.h"
#include "Die-affect.h"
#include "Simon.h"
#include"Camera.h"
#define MAX(a,b) (a>b? a : b)
#define MIN(a,b) (a<b? a : b)
extern int getRandom(int start, int end);
void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	delayTimeWait.update();
	delayTimeAttack.update();
	if (getY() < 250) {
		setAlive(false);
		return;
	}
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive && (Weapon::getInstance()->aniIndex == 2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8 || Weapon::getInstance()->aniIndex == 11 || Weapon::getInstance()->aniIndex == 14 || Weapon::getInstance()->aniIndex == 17)) {
		setAlive(false);
		ScoreBar::getInstance()->increaseScore(RAVEN_SCORE);
		makeDieEffect();
	}
	if (AABBCheck(Simon::getInstance())) {
		setAlive(false);
		makeDieEffect();
	}
	pauseAnimation = false;
	if (!CGame::GetInstance()->GetCurrentScene()->getStopUpdate()) {
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		// turn off collision when die 
		if (isAlive)
			CalcPotentialCollisions(coObjects, coEvents);
		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
			if (rdx != 0 && rdx != dx)
				x += nx * abs(rdx);

			// block every object first!

			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;
		}

		//clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

		/* mặc định là false cho tới khi chạm sàn */
		switch (state)
		{
		case RAVEN_STATE_STAND:
			if (abs(getX() - Simon::getInstance()->getX()) < DISTANCE_X) {
				state = RAVEN_STATE_ATTACK;
				delayTimeAttack.start();
				setPhysicsEnable(true);
			}
			break;
		case RAVEN_STATE_ATTACK:
			if (delayTimeAttack.isTerminated()) {
				setVx(0);
				setVy(0);
				state = RAVEN_STATE_WAIT;
				delayTimeWait.start();
				return;
			}
			calculateOtherPoint();
			if (xDes < getX())
			{
				vx = -RAVEN_VX;

			}
			else
			{
				vx = RAVEN_VX;
			}
			vy = (vx * (yDes - getY()) / (xDes - getX()));
			aniIndex = RAVEN_ACTION_FLY;
			
			break;

		case RAVEN_STATE_WAIT:
			if (delayTimeWait.isTerminated()) {
				state = RAVEN_STATE_ATTACK;
				delayTimeAttack.start();
				calculateOtherPoint();
				if (xDes < getX())
				{
					vx = -RAVEN_VX;

				}
				else
				{
					vx = RAVEN_VX;
				}
				vy = (vx * (yDes - getY()) / (xDes - getX()));
			}
			break;

		default:
			break;
		}
	}
	else
	{
		pauseAnimation = true;
	}

}
void Raven::calculateOtherPoint()
{
	Simon* player = Simon::getInstance();
	auto camera = Camera::getInstance();
	if (getMidX() > player->getMidX() && getX() - camera->getX() > 30)
	{
		xDes = camera->getleft();
	}
	else
	{
		xDes = camera->getRight();
	}

	int yMin = player->getMidY() - 120;

	int yMax = player->getMidY();

	yDes = getRandom(yMin, yMax);
}
void Raven::Render()
{
	if (isAlive)
		animation_set->at(aniIndex)->Render(x, y, frameIndex, direction);
}

Raven::Raven()
{
	state = RAVEN_STATE_STAND;
	aniIndex = RAVEN_ACTION_STAND;
	setCollitionType(COLLISION_TYPE_ENEMY);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	setPhysicsEnable(false);
	setDirection(DIRECTION_RIGHT);
	delayTimeAttack.init(TIME_ATTACK);
	delayTimeWait.init(TIME_AWAIT);
}

Raven::~Raven()
{
}