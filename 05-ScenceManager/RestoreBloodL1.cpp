#include "RestoreBloodL1.h"
#include"Simon.h"
#include "ScoreBar.h"
#include "Simon.h"
#include "Game.h"
#include "Gound.h"
void RestoreBloodL1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (getItemState() == ITEM_STATE_PLAYER_EATED)
		return;
	vy += ITEM_GRAVITY * dt;

	if (Simon::getInstance()->isWin) {
		setPhysicsEnable(true);
		setItemState(ITEM_STATE_VISIBLE) ;
		setWidth(animation_set->at(0)->getFrame(0)->GetSprite()->getWidth());
		setHeight(animation_set->at(0)->getFrame(0)->GetSprite()->getHeight());
	}
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
		onPlayerContact();
	}
	
}

void RestoreBloodL1::onPlayerContact()
{
	ScoreBar::getInstance()->restoreHealth();
}

RestoreBloodL1::RestoreBloodL1()
{
}

RestoreBloodL1::~RestoreBloodL1()
{
}