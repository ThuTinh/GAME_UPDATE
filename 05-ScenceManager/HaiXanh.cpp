#include "HaiXanh.h"
#include"Simon.h"
void HaiXanh::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		Simon::getInstance()->setDoublSub(true);
		Simon::getInstance()->setTripbleSub(false);
		setAlive(false);
		this->onPlayerContact();
	}
}

void HaiXanh::onPlayerContact()
{
}

HaiXanh::HaiXanh()
{
	//setAlive(false);
}

HaiXanh::~HaiXanh()
{
}