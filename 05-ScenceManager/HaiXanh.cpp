#include "HaiXanh.h"
#include"Simon.h"
void HaiXanh::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
//	setAlive(false);
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
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