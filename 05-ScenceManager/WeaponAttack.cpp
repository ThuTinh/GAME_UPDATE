#include "Sword.h"
#include"Simon.h"
#include"ScoreBar.h"
void Sword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		onPlayerContact();


	}
}

void Sword::onPlayerContact()
{
	

}

Sword::Sword()
{
}

Sword::~Sword()
{
}