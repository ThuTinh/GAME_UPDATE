#include "SubWeaponItem.h"
#include"Simon.h"
#include"ScoreBar.h"
void SubWeaponItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		onPlayerContact();


	}
}

void SubWeaponItem::Render()
{
	

}

void SubWeaponItem::onPlayerContact()
{
	ScoreBar::getInstance()->increaseHeartCount(NUMBER_HEART);
}

SubWeaponItem::SubWeaponItem()
{
}

SubWeaponItem::~SubWeaponItem()
{
}