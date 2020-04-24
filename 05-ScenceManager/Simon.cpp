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
	attachDelay.init(80);
	colorDelay.init(300);
	setCollitionType(COLLISION_TYPE_PLAYER);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);



}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	//vx = vy = 0;
	attachDelay.update();
	colorDelay.update();
	if (aniIndex == SIMON_ANI_COLORS) {
		
		if(colorDelay.isTerminated()) {
			Simon::getInstance()->aniIndex = SIMON_ANI_STAND;
		}
		else
		{
			return;
		}
	}
	CGameObject::Update(dt);
	if (!stopCollision) {
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

			//// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
			if (rdx != 0 && rdx != dx)
				x += nx * abs(rdx);

			//// block every object first!

			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;
			//
			// Collision logic with other objects
			//
			for (UINT i = 0; i < coEvents.size(); i++)
			{
				LPCOLLISIONEVENT e = coEvents[i];
				if (!dynamic_cast<Ground*>(e->obj)) {
					e->obj->onCollision(e->obj, e->t, e->nx, e->ny);
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

	}
	
	
	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	switch (state)
	{
	case SIMON_STATE_NORMAL: {
		if (isOnGround) {
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
					
					
						if (isAttack) {
							aniIndex = SIMON_ANI_STAND_USING_SUB;
							//state = SIMON_STATE_ATTACK;
							attachDelay.start();
							if (attachDelay.isTerminated())
							{
								state = SIMON_STATE_NORMAL;
							}
						}
						else
						{
							aniIndex = SIMON_ANI_STAND;
							setVx(0);
						}
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
			
		}
		else
		{
			aniIndex = SIMON_ANI_JUMB;
			//setVy(-0.5);
			if (isAttack) {
				state = SIMON_STATE_ATTACK_JUMP;
				attachDelay.start();

			}
		}
	}
	 break;
	case SIMON_STATE_ATTACK:
	{
		break;
	}
	case SIMON_STATE_ATTACK_JUMP:
	{
		
		aniIndex = SIMON_ANI_DUCK_USING_SUB;
		
		
		if (attachDelay.isTerminated())
		{
			state = SIMON_STATE_NORMAL;
		}
		break;
	}
	case SIMON_STATE_ON_STAIR:
	{
		switch (playerStairState)
		{
		case SIMON_STAIR_STATE_NORUN:
			
			if (!isUpDown && !isDownDown)
			{
				setPauseAnimation(true);
				frameIndex = 0;
				setDx(0);
				setDy(0);
				setX(playerStairDestx);
				setY(playerStairDesty);
			}
			if (isUpDown)
			{
				goStairUp();
			}
			if (isDownDown)
			{
				goStairDown();
			}
			return;
		case SIMON_STAIR_STATE_GO_UP:
			//setDx(getDirection());
			x += getDirection();
			/* đi lên */
			setDy(1);
			y += 1;
			break;
		case SIMON_STAIR_STATE_GO_DOWN:
			//setDx(getDirection());
			x += getDirection();
			/* đi xuống */
			setDy(-1);
			y -= 1;
			break;
		default:
			break;
		}
		/* phương thức xử lý chung khi đi (kiểm tra đến đích chưa để dừng lại) */
		if (playerStairState == SIMON_STAIR_STATE_GO_UP || playerStairState == SIMON_STAIR_STATE_GO_DOWN)
		{
			if (getDirection() == DIRECTION_RIGHT)
			{
				/* đang đi về phía bên phải */
				if (getX() + getDx() > playerStairDestx)
				{
					/* tới vị trí */
					setStartStair();

					setX(playerStairDestx);
					setY(playerStairDesty);

					/* nếu là lần di chuyển cuối cùng */
					if (getIsLastRunStair())
					{
						setY(getY() + 12);
						setX(getX() + 12);
						setStopStair();
					}
				}
			}
			else
			{
				/* đang đi về bên trái */
				if (getX() + getDx() < playerStairDestx)
				{
					/* tới vị trí */
					setStartStair();
					/* đang đi về phía bên trái */

					setX(playerStairDestx);
					setY(playerStairDesty);

					/* nếu là lần di chuyển cuối cùng */
					if (getIsLastRunStair())
					{
						setY(getY() + 10);
						setX(getX() - 10);
						setStopStair();
					}
				}
			}
		}
		break;
	}
	
	default:
		break;
	}

	
	
}

void Simon::Render()
{	
	animation_set->at(aniIndex)->Render(x, y,frameIndex , direction, pauseAnimation);	
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

int Simon::getState()
{
	return state;
}

Simon* Simon::getInstance()
{
	if (instance == 0) {
		instance = new Simon();
	}
	return instance;
}

void Simon::setStartStair()
{

	/* tắt vật lý cho player */
	this->setPhysicsEnable(false);

	playerStairDestx = getX();
	playerStairDesty = getY();


	if (!isUpDown && !isDownDown)
	{
		/* tắt chuyển animation cho player */
		setPauseAnimation(true);

		/* stop tất cả chuyển động */
		this->setVx(0);
		this->setVy(0);
		this->setDx(0);
		this->setDy(0);

		/* reset frame */
		frameIndex = 0;
	}

	/* set state lên cầu thang cho player */
	 state = SIMON_STATE_ON_STAIR;

	/* set player stair state */
	setPlayerStairState(SIMON_STAIR_STATE_NORUN);


	/* tắt xử lý va chạm */
	setStopCollision(true);
}

void Simon::setStopStair()
{
	/* nhưng chuyển động */
	this->setVx(0);
	this->setVy(0);
	this->setDx(0);
	this->setDy(0);

	/* bật chuyển animation cho player */
	setPauseAnimation(false);

	/* bật xử lý va chạm */
	setStopCollision(false);

	/* bật vật lý */
	setPhysicsEnable(true);

	/* chuyển về state normal */
	 state = SIMON_STATE_NORMAL;

	/* tắt chạy stair theo frame cuối */
	setIsLastRunStair(false);
}

bool Simon::getIsLastRunStair()
{
	return  isLastRunStair;
}

void Simon::setIsLastRunStair(bool isLastRunStair)
{
	this->isLastRunStair = isLastRunStair;
}

void Simon::goStairUp()
{
	playerStairDesty = getY() + 8;
	if (stairDirection == 0)
	{
		/* stair phải */
		playerStairDestx += 8;
		setDirection(DIRECTION_LEFT);
	}
	else
	{
		/* stair trái */
		playerStairDestx -= 8;
		setDirection(DIRECTION_RIGHT);
	}

	setPlayerStairState(SIMON_STAIR_STATE_GO_UP);
	/* cho player có lại animation khi lên cầu thang */
	setPauseAnimation(false);
	aniIndex = SIMON_ANI_ASCEND_STAIRS;
}

void Simon::goStairDown()
{
	playerStairDesty -= 8;
	if (stairDirection == 0)
	{
		/* stair phải */
		playerStairDestx -= 8;
		setDirection(DIRECTION_RIGHT);
	}
	else
	{
		/* stair trái */
		playerStairDestx += 8;
		setDirection(DIRECTION_LEFT);
	}

	setPlayerStairState(SIMON_STAIR_STATE_GO_DOWN);
	/* cho player có lại animation khi xuống cầu thang */
	setPauseAnimation(false);
	aniIndex = SIMON_ANI_DESCEN_STAIRS;
}

void Simon::setStairDirection(int stairDirection)
{
	this->stairDirection = stairDirection;
}

void Simon::setPlayerStairState(int playerStairState)
{
	this->playerStairState = playerStairState;
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

