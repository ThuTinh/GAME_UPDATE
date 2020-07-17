#include "Sketon.h"
#include"Gound.h"
#include "Weapon.h"
#include "Die-affect.h"
#include "ScoreBar.h"
#include "Simon.h"
#include "Game.h"
#include "WhiteBone.h"
void Sketon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*delayJumb.update();
	timeJumb.update();
	if (getX() < 288) {
		if (timeJumb.isOnTime())
		{
			setStateSketon(SKETON_NOMAL);

		}
		if (timeJumb.isTerminated()) {
			delayJumb.start();
			if (delayJumb.isOnTime()) {
				setStateSketon(SKETON_JUMB);
				setVx(0.05);
				setVy(0.07);
			}
		}
		if (delayJumb.isTerminated())
		{
			timeJumb.start();
			setVx(-0.05);
			setVy(0.06);
		}
	}
	else
	{
		setStateSketon(SKETON_NOMAL);
	}*/
	
		
		
	
	vy += ENEMY_GRAVITY * dt;
	whiteBoneDelay.update();
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive && (Weapon::getInstance()->aniIndex == 2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8 || Weapon::getInstance()->aniIndex == 11 || Weapon::getInstance()->aniIndex == 14 || Weapon::getInstance()->aniIndex == 17)) {
		setAlive(false);
		ScoreBar::getInstance()->increaseScore(SKETON_SCORE);
		DieEffect* dieEffect = new DieEffect();
		CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(dieEffect);
		dieEffect->setX(getMidX());
		dieEffect->setY(getMidY());
		dieEffect->setAlive(true);
		dieEffect->timeDelay.start();
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	pauseAnimation = false;
	if (!CGame::GetInstance()->GetCurrentScene()->getStopUpdate()) {
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
					if (stateSKeton == SKETON_NOMAL)
					{

						onCollision(e->obj, e->t, e->nx, e->ny);
						/*vx = 0;
						vy = 0;*/


					}
					else
					{
						/*	setVx( getDirection()* 0.04);
							setVy(0.02);*/
					}

				}
			}
		}

		//clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		if (Simon::getInstance()->getX() < getX()) {
			setDirection(DIRECTION_LEFT);
		}
		else
		{
			setDirection(DIRECTION_RIGHT);
		}
		//Simon::getInstance()->getY() > getY() &&
		if (abs(Simon::getInstance()->getX() - getX()) <= DISTANCE_TO_THROW_WHITEBONE) {
			if (timeThrow.atTime()) {
				WhiteBone* whiteBone = new WhiteBone();
				CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(whiteBone);
				whiteBone->setX(getMidX());
				whiteBone->setY(getMidY());
				whiteBone->setAlive(true);
				whiteBone->setPhysicsEnable(true);
				whiteBone->timeDelay.start();
			}
		}
	}
	else
	{
		setPauseAnimation(true);
	}
	Enemy::Update(dt, coObjects);

}

void Sketon::onCollision(CGameObject* other, float collisionTime, int nx, int ny)
{
	if (this->getX() + 5 > other->getRight() || nx == -1) {
		setVx(-SKETON_VX);
	}
	else
	{
		if (this->getX() - 5 < other->getLeft() || nx == 1) {
			setVx(SKETON_VX);
		}
	}
}

SKETON_STATE Sketon::getStateSketon()
{
	return stateSKeton;
}

void Sketon::setStateSketon(SKETON_STATE state)
{
	stateSKeton = state;
}

void Sketon::Render()
{
	if (isAlive)
		animation_set->at(0)->Render(x, y, frameIndex, direction, pauseAnimation);
}

Sketon::Sketon()
{
	setCollitionType(COLLISION_TYPE_ENEMY);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	setPhysicsEnable(true);
	setDirection(DIRECTION_RIGHT);
	setVx(0.03);
	whiteBoneDelay.init(10);
	timeThrow.init(3000);
	timeJumb.init(10000);
	delayJumb.init(100);
	timeJumb.start();
	
}

Sketon::~Sketon()
{
}