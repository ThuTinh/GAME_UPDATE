#include "TripbleSub.h"
#include"Simon.h"
void TripbleSub::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	setVy(TRIPBLE_VY);
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		Simon::getInstance()->setDoublSub(false);
		Simon::getInstance()->setTripbleSub(true);
		ScoreBar::getInstance()->setHasDoubleSub(false);
		ScoreBar::getInstance()->setHasTripbleSub(true);
		onPlayerContact();
	}
}

void TripbleSub::onPlayerContact()
{
}

TripbleSub::TripbleSub()
{
	//setAlive(false);
}

TripbleSub::~TripbleSub()
{
}