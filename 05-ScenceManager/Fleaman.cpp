#include "Fleaman.h"
#include "Simon.h"
#include"Gound.h"
#include "Enemy.h"
//void Fleaman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//
//	vy += ENEMY_GRAVITY * dt;
//	CGameObject::Update(dt);
//	vector<LPCOLLISIONEVENT> coEvents;
//	vector<LPCOLLISIONEVENT> coEventsResult;
//	coEvents.clear();
//
//
//	// turn off collision when die 
//	if (isAlive)
//		CalcPotentialCollisions(coObjects, coEvents);
//
//
//	// No collision occured, proceed normally
//	if (coEvents.size() == 0)
//	{
//		x += dx;
//		y += dy;
//	}
//	else
//	{
//		float min_tx, min_ty, nx = 0, ny;
//		float rdx = 0;
//		float rdy = 0;
//
//		// TODO: This is a very ugly designed function!!!!
//		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
//
//		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
//		if (rdx != 0 && rdx != dx)
//			x += nx * abs(rdx);
//
//		// block every object first!
//
//		x += min_tx * dx + nx * 0.4f;
//		y += min_ty * dy + ny * 0.4f;
//
//		for (UINT i = 0; i < coEvents.size(); i++)
//		{
//			LPCOLLISIONEVENT e = coEvents[i];
//			if (!dynamic_cast<Ground*>(e->obj)) {
//
//			}
//			else
//			{
//
//
//			}
//
//		}
//
//	}
//
//	//clean up collision events
//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
//	/* mặc định là false cho tới khi chạm sàn */
//
//}

void Fleaman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	if (abs(Simon::getInstance()->getX() - getX()) < FLEAMAN_DISTANCE_TO_JUMB) {
		setPhysicsEnable(true);
		setDirectionFollowPlayer();
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