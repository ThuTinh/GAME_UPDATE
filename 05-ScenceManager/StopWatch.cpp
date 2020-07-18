#include "StopWatch.h"
#include"Simon.h"
void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		this->onPlayerContact();
	}
}

void StopWatch::onPlayerContact()
{
	ScoreBar::getInstance()->setTypeSubWeapon(TYPE_SUBWEAPON::STOPWATCH);
}

StopWatch::StopWatch()
{
	//setAlive(false);
}

StopWatch::~StopWatch()
{
}