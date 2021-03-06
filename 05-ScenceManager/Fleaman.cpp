﻿#include "Fleaman.h"
#include "Simon.h"
#include"Gound.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Die-affect.h"
#include "ScoreBar.h"
#include "Game.h"

void Fleaman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += FLEAMAN_GRAVITY * dt;
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive && (Weapon::getInstance()->aniIndex == 2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8 || Weapon::getInstance()->aniIndex == 11 || Weapon::getInstance()->aniIndex == 14 || Weapon::getInstance()->aniIndex == 17)) {
		setAlive(false);
		ScoreBar::getInstance()->increaseScore(FLEAMAN_SCORE);
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

		if (abs(Simon::getInstance()->getX() - getX()) < FLEAMAN_DISTANCE_TO_JUMB && Simon::getInstance()->getY() < 130) {
			setPhysicsEnable(true);
			if (abs(Simon::getInstance()->getX() - getX()) > FLEAMAN_DISTANCE_STOP) {
				setDirectionFollowPlayer();
			}

			switch (fleamanState)
			{
			case FLEAMAN_STATE_TO_JUMB:
				setVx(getDirection() * FLEAMAN_VX_WHEN_JUM);
				setVy(FLEAMAN_VY_WHEN_JUMB);
				fleamanState = FLEAMAN_STATE_JUMP_SHORT;
				break;
			case FLEAMAN_STATE_JUMP_SHORT:
				setVx(getDirection() * FLEAMAN_VX_SHORT);
				if (getIsOnGround())
				{
					if (jumpRemain > 0)
					{
						setVy(FLEAMAN_VY_SHORT);
						jumpRemain--;
					}
					else
					{
						fleamanState = FLEAMAN_STATE_JUMP_LONG;
						jumpRemain = FLEAMAN_JUMBLONG_COUNTER;
					}
				}
				break;
			case FLEAMAN_STATE_JUMP_LONG:
				setVx(getDirection() * FLEAMAN_VX_LONG);
				if (getIsOnGround())
				{
					if (jumpRemain > 0)
					{
						setVy(FLEAMAN_VY_LONG);
						jumpRemain--;
					}
					else
					{
						fleamanState = FLEAMAN_STATE_JUMP_SHORT;
						jumpRemain = FLEAMAN_FUMBSHORT_COUNTER;
					}
				}
				break;
			default:
				break;
			}
		}
	}
	else
	{
		pauseAnimation = true;
	}

	Enemy::Update(dt, coObjects);
}

void Fleaman::Render()
{
	if (isAlive)
		animation_set->at(0)->Render(x, y, frameIndex, direction, pauseAnimation);
}

void Fleaman::restorePosition()
{
	Enemy::restorePosition();
	setPhysicsEnable(false);
	fleamanState = FLEAMAN_STATE_TO_JUMB;
	aniIndex = FLEAMAN_ACTION_STAND;
	setDirection(DIRECTION_RIGHT);
	setVx(0);
	setVy(0);
}

Fleaman::Fleaman()
{
	setCollitionType(COLLISION_TYPE_ENEMY);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	setPhysicsEnable(false);
	setVx(0);
	setVy(0);
	setDirection(DIRECTION_RIGHT);
	aniIndex = FLEAMAN_ACTION_STAND;
	fleamanState = FLEAMAN_STATE_TO_JUMB;
	jumpRemain = FLEAMAN_FUMBSHORT_COUNTER;
}

Fleaman::~Fleaman()
{
}