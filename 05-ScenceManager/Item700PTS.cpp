#include "Item700PTS.h"
#include"Simon.h"
void Item700PTS::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		this->onPlayerContact();


	}
}

Item700PTS::Item700PTS()
{
}

Item700PTS::~Item700PTS()
{
}