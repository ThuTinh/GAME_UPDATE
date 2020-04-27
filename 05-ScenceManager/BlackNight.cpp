﻿#include "BlackNight.h"
#include"Gound.h"
#include"Simon.h"
#include"ScoreBar.h"
#include"Weapon.h"
#include"Die-affect.h"
#include"Game.h"
void BlackNight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy += ENEMY_GRAVITY * dt;
	CGameObject::Update(dt);
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive) {
		setAlive(false);
		ScoreBar::getInstance()->increaseScore(BLACKNIGHT_SCORE);
		DieEffect *dieEffect = new DieEffect();
		CGame::GetInstance()->GetCurrentScene()->addObject(dieEffect);
		dieEffect->setX(getMidX());
		dieEffect->setY(getMidY());
		dieEffect->setAlive(true);
		dieEffect->timeDelay.start();

	}
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

		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (!dynamic_cast<Ground*>(e->obj)) {
				
			}
			else
			{
				if (this->getX() + 5 > e->obj->getRight() || nx ==-1) {
					setDirection(DIRECTION_LEFT);
					setVx(-BLACKNIGHT_VX);
				
				}
				else
				{
					if (this->getX() - 5 < e->obj->getLeft() || nx==1 ) {
						setDirection(DIRECTION_RIGHT);
						//x += 1;
						setVx(BLACKNIGHT_VX);
					}
				}
				
			}

		}

	}
	//clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	/* mặc định là false cho tới khi chạm sàn */
	
	
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
}

BlackNight::~BlackNight()
{
}