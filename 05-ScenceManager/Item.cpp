﻿#include "Item.h"
#include"Weapon.h"
#include "Gound.h"
#include "Game.h"
#include "BigHeart.h"
#include "SubWeaponAttack.h"
#include "money-effect.h"
Item::Item()
{
	itemState = ITEM_STATE_INVISIBLE;
	setPhysicsEnable(false);
	setCollitionType(COLLISION_TYPE_MISC);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	delayVisible.init(3000);
}


void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	delayVisible.update();
	if (itemState == ITEM_STATE_PLAYER_EATED)
		return;
	

	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive()  && isAlive && (Weapon::getInstance()->aniIndex == 2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8 || Weapon::getInstance()->aniIndex == 11 || Weapon::getInstance()->aniIndex == 14|| Weapon::getInstance()->aniIndex == 17)) {
		setPhysicsEnable(true);
		//setVy(ITEM_VY);
		itemState = ITEM_STATE_VISIBLE;
		delayVisible.start();
		setWidth(animation_set->at(0)->getFrame(0)->GetSprite()->getWidth());
		setHeight(animation_set->at(0)->getFrame(0)->GetSprite()->getHeight());
	}
	if (CGame::GetInstance()->GetCurrentScene()->getAddtionalObject().size() > 0 && isAlive && itemState != ITEM_STATE_VISIBLE) {
		vector<LPGAMEOBJECT> listObject = CGame::GetInstance()->GetCurrentScene()->getAddtionalObject();
		for (size_t i = 0; i < listObject.size(); i++)
		{
			if (dynamic_cast<SubWeaponAttack*>(listObject[i]) && listObject[i]->isAlive) {
				if (AABBCheck(listObject[i])) {
					//setVy(ITEM_VY);
					setPhysicsEnable(true);
					itemState = ITEM_STATE_VISIBLE;
					setWidth(animation_set->at(0)->getFrame(0)->GetSprite()->getWidth());
					setHeight(animation_set->at(0)->getFrame(0)->GetSprite()->getHeight());
				}
			}
		}
	}
	if (delayVisible.isTerminated()) {
		setAlive(false);
	}
	vy += ITEM_GRAVITY * dt;
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
}

void Item::Render()
{
	if (itemState == ITEM_STATE_VISIBLE) {
		animation_set->at(0)->Render(x, y, frameIndex,DIRECTION_LEFT);
	}
}

void Item::SetState(int state)
{


}

void Item::setItemState(ITEM_STATE itemState)
{
	this->itemState = itemState;
}

ITEM_STATE Item::getItemState()
{
	return itemState;
}

void Item::onPlayerContact()
{
	
}

void Item::restorePosition()
{
	CGameObject::restorePosition();
	itemState = ITEM_STATE_INVISIBLE;
	setPhysicsEnable(false);
	
}

void Item::makeMoneyEffect(int aniIdx)
{
	MoneyEffect* effect = new MoneyEffect();
	CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(effect);
	effect->setX(getMidX() + 10);
	effect->setY(getMidY() + 10);
	effect->setAlive(true);
	effect->aniIndex = aniIdx;
	effect->timeDelay.start();
}
