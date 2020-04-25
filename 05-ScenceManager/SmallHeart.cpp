#include "SmallHeart.h"
#include"Simon.h"
void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		this->onPlayerContact();


	}
}



SmallHeart::SmallHeart()
{
}

SmallHeart::~SmallHeart()
{
}