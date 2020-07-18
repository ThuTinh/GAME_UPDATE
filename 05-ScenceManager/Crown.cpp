#include "Crown.h"
#include"Simon.h"
#include "Weapon.h"
#include "Gound.h"
#include "ScoreBar.h"
#include "money-effect.h"
#include "Game.h"
void Crown::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*Item::Update(dt, coObjects);*/
	delayVisible.update();
	if (getItemState() == ITEM_STATE_PLAYER_EATED)
		return;
	vy += ITEM_GRAVITY * dt;
	if (delayVisible.isTerminated()) {
		setAlive(false);
		this->setItemState(ITEM_STATE_INVISIBLE);
	}
	if (Simon::getInstance()->getNumberObjectBlack() >= 2) {
		if (!checkOnlyOne) {
			setItemState(ITEM_STATE_VISIBLE);
			checkOnlyOne = true;
			delayVisible.start();
			setPhysicsEnable(true);
		}
		
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
	/* mặc định là false cho tới khi chạm sàn */
	
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		ScoreBar::getInstance()->increaseScore(SCORE);
		MoneyEffect* effect = new MoneyEffect();
		CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(effect);
		effect->setX(getMidX() + 10);
		effect->setY(getMidY() + 10);
		effect->setAlive(true);
		effect->aniIndex = 4;
		effect->timeDelay.start();
		this->onPlayerContact();
	}

}

void Crown::restorePosition()
{
	Item::restorePosition();
	checkOnlyOne = false;
	Simon::getInstance()->setNumberObjectBlack(0);
}


Crown::Crown()
{
	delayVisible.init(3500);
	checkOnlyOne = false;
	
}

Crown::~Crown()
{
}