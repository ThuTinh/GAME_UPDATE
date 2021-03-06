#include "StopWatch.h"
#include"Simon.h"
void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	setVy(STOPWATCH_VY);
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		onPlayerContact();
	}
}

void StopWatch::onPlayerContact()
{
	ScoreBar::getInstance()->setTypeSubWeapon(TYPE_SUBWEAPON::STOPWATCH);
}

StopWatch::StopWatch()
{

}

StopWatch::~StopWatch()
{
}