﻿#include "Ghost.h"
#include"Gound.h"
#include "Game.h"
#include "Weapon.h"
#include "ScoreBar.h"
#include "Die-affect.h"
#include "Simon.h"
#include "SubWeaponAttack.h"
#include"hit-effect.h"

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timeDelay.update();
	timeHurtDelay.update();

  if (isRender) {
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive && (Weapon::getInstance()->aniIndex == 2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8 || Weapon::getInstance()->aniIndex == 11 || Weapon::getInstance()->aniIndex == 14 || Weapon::getInstance()->aniIndex == 17)) {
		state = GHOST_STATE_HURT;
		timeHurtDelay.start();
		timeDelay.start();
		makeHitEffect();

	}
	if (CGame::GetInstance()->GetCurrentScene()->getAddtionalObject().size() > 0 && isAlive) {
		vector<LPGAMEOBJECT> listObject = CGame::GetInstance()->GetCurrentScene()->getAddtionalObject();
		for (size_t i = 0; i < listObject.size(); i++)
		{
			if (dynamic_cast<SubWeaponAttack*>(listObject[i]) && listObject[i]->isAlive) {
				if (AABBCheck(listObject[i])) {
					timeDelay.start();
					state = GHOST_STATE_HURT;
					timeHurtDelay.start();
				}
			}
		}
	}
	if (timeDelay.isTerminated()) {
		++counterInjured;
		if (Simon::getInstance()->getNumberArchery()==0)
		{
			if (counterInjured >= COUNTER_LIFE_NOMAL) {
				setAlive(false);
				ScoreBar::getInstance()->increaseScore(GHOST_SCORE);
				makeDieEffect();
			}
		}
		else
		{
			if (counterInjured >= COUNTER_LIFE) {
				setAlive(false);
				ScoreBar::getInstance()->increaseScore(GHOST_SCORE);
				makeDieEffect();
			}
		}
		
	}
	Enemy::Update(dt, coObjects);
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
		if (abs(Simon::getInstance()->getX() - getX()) > GHOST_DISTANCE_STOP) {
			setDirectionFollowPlayer();
		}
		//setDirectionFollowPlayer();
	}
	else
	{
		pauseAnimation = true;
	}
  }
	switch (state)
	{
	case GHOST_STATE_STAND:
		if (getX() - Simon::getInstance()->getX() > DISTANCE_X) {
			
			state = GHOST_STATE_ATTACK;
			setIsRender(true);
			setPhysicsEnable(true);
		}
		break;
	case GHOST_STATE_ATTACK:	
		setVx(getDirection() * VX_GHOST);
		aniIndex = GHOST_ACTION_FLY;
		if (Simon::getInstance()->getY() - getY() > 5) {
			setVy(VY_GHOST);
		}
		else
		{
			if(getY()- Simon::getInstance()->getY()>3)
				setVy(-VY_GHOST);
			else
			{
				setVy(0);
			}
		}
		break;
	case GHOST_STATE_HURT:
		setVx(0);
		if (timeHurtDelay.isTerminated()) {
			state = GHOST_STATE_ATTACK;
		}
		break;
	default:
		break;
	}
}

void Ghost::Render()
{
	if (!isRender)
		return;
	if (isAlive)
		animation_set->at(aniIndex)->Render(x, y, frameIndex, direction);
}

void Ghost::setIsRender(bool render)
{
	this->isRender = render;
}

bool Ghost::getIsRender()
{
	return isRender;
}

Ghost::Ghost()
{
	setVy(0);
	state = GHOST_STATE_STAND;
	aniIndex = GHOST_ACTION_STAND;
	setCollitionType(COLLISION_TYPE_ENEMY);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	setPhysicsEnable(false);
	setDirection(DIRECTION_LEFT);
	setIsRender(false);
	timeDelay.init(20);
	timeHurtDelay.init(500);
	counterInjured = 0;
}

Ghost::~Ghost()
{
}