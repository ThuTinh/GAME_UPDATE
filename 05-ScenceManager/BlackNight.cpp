﻿#include "BlackNight.h"
#include"Gound.h"
#include"Simon.h"
#include"ScoreBar.h"
#include"Weapon.h"
#include"Die-affect.h"
#include "Game.h"
#include "BigHeart.h"
void BlackNight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ENEMY_GRAVITY * dt;
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive) {
		++counterInjured;
		if (counterInjured >= COUNTER_LIFE) {
			setAlive(false);
			ScoreBar::getInstance()->increaseScore(ENEMY_SCORE);
			DieEffect* dieEffect = new DieEffect();
			CGame::GetInstance()->GetCurrentScene()->addObject(dieEffect);
			dieEffect->setX(getMidX());
			dieEffect->setY(getMidY());
			dieEffect->setAlive(true);
			dieEffect->timeDelay.start();
			int r = rand();
			if (r % 2 == 0) {
				BigHeart* bigHeart = new BigHeart();
				bigHeart->animation_set = CAnimationSets::GetInstance()->Get(ID_ANI_HEART);
				CGame::GetInstance()->GetCurrentScene()->addObject(bigHeart);
				bigHeart->setX(getMidX());
				bigHeart->setY(getMidY());
				bigHeart->setAlive(true);
			}
		}
	}
	CGameObject::Update(dt);
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

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (!dynamic_cast<Ground*>(e->obj)) {
				x += dx;
			}
			else
			{
				onCollision(e->obj, e->t, e->nx, e->ny);

			}
		}
	}
	//clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	/* mặc định là false cho tới khi chạm sàn */
}

void BlackNight::onCollision(CGameObject* other, float collisionTime, int nx, int ny)
{
	if (this->getX() + 5 > other->getRight() || nx == -1) {
		setDirection(DIRECTION_LEFT);
		setVx(-BLACKNIGHT_VX);

	}
	else
	{
		if (this->getX() - 5 < other->getLeft() || nx == 1) {
			setDirection(DIRECTION_RIGHT);
			//x += 1;
			setVx(BLACKNIGHT_VX);
		}
	}
}

void BlackNight::Render()
{
	if(isAlive)
		animation_set->at(0)->Render(x, y, frameIndex, direction);
}

BlackNight::BlackNight()
{
	setCollitionType(COLLISION_TYPE_ENEMY);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	setPhysicsEnable(true);
	setDirection(DIRECTION_RIGHT);
	setVx(BLACKNIGHT_VX);
	counterInjured = 0;
}

BlackNight::~BlackNight()
{
}