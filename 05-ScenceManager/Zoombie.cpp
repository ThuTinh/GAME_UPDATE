#include "Zoombie.h"
#include"Gound.h"
#include "Simon.h"
#include "ScoreBar.h"
#include "Die-affect.h"
#include "Camera.h"
#include "Weapon.h"
#include"Game.h"
void Zoombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy += ZOOMBIE_GRAVITY * dt;
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive) {
		setAlive(false);
		ScoreBar::getInstance()->increaseScore(ZOOMBIE_SCORE);
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

		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
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

	switch (state)
	{
	case ZOOMBIE_STAND:
		if (abs(getX() - Simon::getInstance()->getX()) < ZOOMBIE_RUN_DX) {
			state = ZOOMBIE_RUN;
		}
		break;
	case ZOOMBIE_RUN:
		setVx(-ZOOMBIE_RUN_VX);
		if (abs(Camera::getInstance()->getSpace()->X - getX()) < 30) {
			state = ZOOMBIE_RUN_TURNING;
		}

		if (abs(Simon::getInstance()->getX() - getX()) > ZOOMBIE_RUN_DX_TO_TURNING) {
			state = ZOOMBIE_RUN_TURNING;
		}
		break;

	case ZOOMBIE_RUN_TURNING:
		setVx(ZOOMBIE_RUN_VX);
		break;

	default:
		break;
	}
}

void Zoombie::Render()
{
	animation_set->at(0)->Render(x, y, frameIndex, direction);
}

Zoombie::Zoombie()
{
	setCollitionType(COLLISION_TYPE_ENEMY);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	setPhysicsEnable(true);
	setDirection(DIRECTION_RIGHT);
}

Zoombie::~Zoombie()
{
}