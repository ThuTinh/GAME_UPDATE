#include "Item700PTS.h"
#include"Simon.h"
#include"ScoreBar.h"
void Item700PTS::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		onPlayerContact();
	}
}

void Item700PTS::onPlayerContact()
{
	ScoreBar::getInstance()->increaseScore(ITEM700PTS_SCORE);
}

Item700PTS::Item700PTS()
{
}

Item700PTS::~Item700PTS()
{
}