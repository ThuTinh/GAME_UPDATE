#include "BluePotion.h"
#include"Simon.h"
void BluePotion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		this->onPlayerContact();


	}
}

BluePotion::BluePotion()
{
}

BluePotion::~BluePotion()
{
}