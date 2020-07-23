#include "HaiXanh.h"
#include"Simon.h"
void HaiXanh::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	setVy(HAIXANH_VY);
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		Simon::getInstance()->setDoublSub(true);
		Simon::getInstance()->setTripbleSub(false);
		ScoreBar::getInstance()->setHasDoubleSub(true);
		ScoreBar::getInstance()->setHasTripbleSub(false);


		setAlive(false);
	}
}


HaiXanh::HaiXanh()
{
	//setAlive(false);
}

HaiXanh::~HaiXanh()
{
}