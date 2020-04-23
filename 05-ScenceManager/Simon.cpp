#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Simon.h"
#include "Game.h"
#include "Gound.h"

Simon *Simon::instance = 0;
Simon::Simon() : CGameObject()
{
	setCollitionType(COLLISION_TYPE_GROUND);
	setPhysicsEnable(true);
	setVx(0);
	//setVy(SIMON_JUMP_Y);
	setAlive(true);
	setDirection(DIRECTION_RIGHT);
	SetState(SIMON_STATE_NORMAL);
	setNumberArchery(1);
	attachDelay.init(100);

}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	//vx = vy = 0;
	attachDelay.update();
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




//
// Collision logic with other objects
//
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
			//Ground* ground = dynamic_cast<Ground*>(e->obj);
		}

	}


	//clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	/* mặc định là false cho tới khi chạm sàn */

	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	switch (state)
	{
	case SIMON_STATE_NORMAL: {
		if (getIsOnGround()) {
			if (isRightDown) {
				setDirection(DIRECTION_RIGHT);
				aniIndex = SIMON_ANI_GO;
				setVx(SIMON_VX);
			}
			else
			{
				if (isLeftDown) {
					aniIndex = SIMON_ANI_GO;
					setDirection(DIRECTION_LEFT);
					setVx(-SIMON_VX);
				}
				else
				{
					aniIndex = SIMON_ANI_STAND;
					setVx(0);
				}
			}
			if (isJumpDown) {
				aniIndex = SIMON_ANI_JUMB;
				setVy(SIMON_JUMP_Y);
				attachDelay.start();
				if (attachDelay.isTerminated())
				{
					state = SIMON_STATE_NORMAL;
				}
				
			}
			else
			{

				if (isAttack) {
					aniIndex = SIMON_ANI_STAND_USING_SUB;
					//state = SIMON_STATE_ATTACK;
					attachDelay.start();
					if (attachDelay.isTerminated())
					{
						state = SIMON_STATE_NORMAL;
					}
				}
			}
		}
		else
		{
			/*aniIndex = SIMON_ANI_JUMB;
			if (isAttack) {
				state = SIMON_STATE_ATTACK_JUMP;
				attachDelay.start();
				
			}*/
		}
	}
	 break;
	case SIMON_STATE_ATTACK_JUMP:
	{
		
		aniIndex = SIMON_ANI_DUCK_USING_SUB;
		setVy(SIMON_JUMP_Y);
		if (attachDelay.isTerminated())
		{
			state = SIMON_STATE_NORMAL;
		}
	}
	break;
	default:
		break;
	}

	
	
}

void Simon::Render()
{	
	animation_set->at(aniIndex)->Render(x, y,frameIndex , direction);	
}

void Simon::setNumberArchery(int num)
{
	this->numberArchery = num;
}

int Simon::getNumberArchery()
{
	return numberArchery;
}

void Simon::addNumberArchery(int num)
{
	this->numberArchery += num;
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);

	//switch (state)
	//{
	//case MARIO_STATE_WALKING_RIGHT:
	//	vx = MARIO_WALKING_SPEED;
	//	nx = 1;
	//	break;
	//case MARIO_STATE_WALKING_LEFT: 
	//	vx = -MARIO_WALKING_SPEED;
	//	nx = -1;
	//	break;
	//case MARIO_STATE_JUMP: 
	//	vy = -MARIO_JUMP_SPEED_Y;
	//case MARIO_STATE_IDLE: 
	//	vx = 0;
	//	break;
	//case MARIO_STATE_DIE:
	//	vy = -MARIO_DIE_DEFLECT_SPEED;
	//	break;
	//}
}

Simon* Simon::getInstance()
{
	if (instance == 0) {
		instance = new Simon();
	}
	return instance;
}

void Simon::onCollision(CGameObject* other, float collisionTime, int nx, int ny)
{
	CGameObject::onCollision( other,  collisionTime,  nx,  ny);
}

//void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
//{
//	left = x;
//	top = y; 
//	right = x + getWidth();
//	bottom = y + getHeight();
//	
//}

