#include "Raven.h"
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
	if (AABBCheck(Simon::getInstance())) {
		setAlive(false);
		DieEffect* dieEffect = new DieEffect();
		CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(dieEffect);
		dieEffect->setX(getMidX());
		dieEffect->setY(getMidY());
		dieEffect->setAlive(true);
		dieEffect->timeDelay.start();
	}
	Enemy::Update(dt, coObjects);
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
			calculateOtherPoint();
			if (xDes < getX())
			{
				vx = -RAVEN_VX;
				setDirection(DIRECTION_LEFT);

			}
			else
			{
				vx = RAVEN_VX;
				setDirection(DIRECTION_RIGHT);
			}
			vy = (vx * (yDes - getY()) / (xDes - getX() -2));
			/*setVy(RAVEN_VY);
			setVx(getDirection() * RAVEN_VX);*/
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
	else
	{
		pauseAnimation = true;
	}
	vy += RAVEN_GRAVITY * dt;
	

}
void Raven::calculateOtherPoint()
{
	Simon* player = Simon::getInstance();
	auto camera = Camera::getInstance();
	if (getMidX() > player->getMidX() && getX() - camera->getX() > 40)
	{
		xDes = camera->getleft();
	}
	else
	{
		xDes = camera->getRight();
	}

	int yMin = player->getMidY() - 60;

	int yMax = player->getMidY()+20;

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
	
}

Raven::~Raven()
{
}