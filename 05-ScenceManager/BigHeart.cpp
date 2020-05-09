#include "BigHeart.h"
#include"Simon.h"
#include "ScoreBar.h"
void BigHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		onPlayerContact();
		

	}
}

void BigHeart::onPlayerContact()
{
	ScoreBar::getInstance()->increaseHeartCount(5);
}

BigHeart::BigHeart()
{
}

BigHeart::~BigHeart()
{
}