#include "Raven.h"
#include"Gound.h"
#include "Game.h"
#include "Weapon.h"
#include "ScoreBar.h"
#include "Die-affect.h"
#include "Simon.h"
void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy += RAVEN_GRAVITY * dt;
	if (getY() < 240) {
		setAlive(false);
		return;
	}
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive && (Weapon::getInstance()->aniIndex == 2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8 || Weapon::getInstance()->aniIndex == 11 || Weapon::getInstance()->aniIndex == 14 || Weapon::getInstance()->aniIndex == 17)) {
			setAlive(false);
			ScoreBar::getInstance()->increaseScore(RAVEN_SCORE);
			DieEffect* dieEffect = new DieEffect();
			CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(dieEffect);
			dieEffect->setX(getMidX());
			dieEffect->setY(getMidY());
			dieEffect->setAlive(true);
			dieEffect->timeDelay.start();
	}
	Enemy::Update(dt, coObjects);
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

		/*for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (!dynamic_cast<Ground*>(e->obj)) {

			}
			else
			{


			}

		}*/

	}

	//clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	/* mặc định là false cho tới khi chạm sàn */
	switch (state)
	{
	case RAVEN_STATE_STAND:
		if (abs(getX() - Simon::getInstance()->getX()) < DISTANCE_X) {
			if (abs(Simon::getInstance()->getX() - getX()) > RAVEN_DISTANCE_STOP) {
				setDirectionFollowPlayer();
			}
			state = RAVEN_STATE_ATTACK;
			setPhysicsEnable(true);
		}
		break;
	case RAVEN_STATE_ATTACK:
		if (Simon::getInstance()->getX() - getX() > DISTANCE_X) {
			setDirection(DIRECTION_RIGHT);
		}
		else
		{
			if(Simon::getInstance()->getX() < getX())
				setDirection(DIRECTION_LEFT);
		}
		setVy(VY);
		setVx(getDirection() * VX);
		aniIndex = RAVEN_ACTION_FLY;
		/*if (getY()> Simon::getInstance()->getY())
		{
			setAlive(false);
		}*/
		break;
	default:
		break;
	}

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
	
}

Raven::~Raven()
{
}