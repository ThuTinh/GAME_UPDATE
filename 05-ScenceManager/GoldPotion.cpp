#include "GoldPotion.h"
#include"Simon.h"
void GoldPotion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	setVy(GOLD_VY);
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		onPlayerContact();
	}
}

void GoldPotion::onPlayerContact()
{
	Simon::getInstance()->setHide();
}

GoldPotion::GoldPotion()
{
}

GoldPotion::~GoldPotion()
{
}