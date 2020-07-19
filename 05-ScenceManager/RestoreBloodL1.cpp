#include "RestoreBloodL1.h"
#include"Simon.h"
#include "ScoreBar.h"
void RestoreBloodL1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		onPlayerContact();
	}
}

void RestoreBloodL1::onPlayerContact()
{
	ScoreBar::getInstance()->increaseHeartCount(5);
}

RestoreBloodL1::RestoreBloodL1()
{
}

RestoreBloodL1::~RestoreBloodL1()
{
}