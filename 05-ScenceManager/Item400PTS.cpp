#include "Item400PTS.h"
#include"Simon.h"
#include"ScoreBar.h"
void Item400PTS::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		this->onPlayerContact();
	}
}

void Item400PTS::onPlayerContact()
{
	ScoreBar::getInstance()->increaseScore(ITEM400PTS_SCORE);
	
}

Item400PTS::Item400PTS()
{
}

Item400PTS::~Item400PTS()
{
}