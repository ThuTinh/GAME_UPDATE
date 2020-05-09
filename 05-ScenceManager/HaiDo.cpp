#include "HaiDo.h"
#include"Simon.h"
void HaiDo::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		this->onPlayerContact();


	}
}

void HaiDo::onPlayerContact()
{
}

HaiDo::HaiDo()
{
}

HaiDo::~HaiDo()
{
}