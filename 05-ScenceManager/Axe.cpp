#include "Axe.h"
#include"Simon.h"
#include "ScoreBar.h"
void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		onPlayerContact();
	}
}

void Axe::onPlayerContact()
{
	ScoreBar::getInstance()->setTypeSubWeapon(TYPE_SUBWEAPON::AXE);
}

Axe::Axe()
{
}

Axe::~Axe()
{
}