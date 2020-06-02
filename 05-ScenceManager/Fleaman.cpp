#include "Fleaman.h"
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
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive) {
		setAlive(false);
		ScoreBar::getInstance()->increaseScore(FLEAMAN_SCORE);
		DieEffect *dieEffect = new DieEffect();
		CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(dieEffect);
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

	if (abs(Simon::getInstance()->getX() - getX()) < FLEAMAN_DISTANCE_TO_JUMB ) {
		setPhysicsEnable(true);
		if (abs(Simon::getInstance()->getX() - getX()) > FLEAMAN_DISTANCE_STOP) {
			setDirectionFollowPlayer();

		}
		setVx(getDirection() * FLEAMAN_VX);
		switch (fleamanState)
		{
		case FLEAMAN_STATE_JUMP_SHORT:
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
	Enemy::Update(dt, coObjects);
}

void Fleaman::Render()
{
	if (isAlive)
		animation_set->at(0)->Render(x, y, frameIndex, direction);
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
	fleamanState = FLEAMAN_STATE_JUMP_SHORT;
	jumpRemain = FLEAMAN_FUMBSHORT_COUNTER;
}

Fleaman::~Fleaman()
{
}