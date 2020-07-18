#include "RestoreBlood.h"
#include"Simon.h"
#include"ScoreBar.h"
void RestoreBlood::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	setVx(HEART_SMALL_VX);
	setVy(HEART_SMALL_VY);
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		onPlayerContact();
	}
}

void RestoreBlood::Render()
{
	if (getItemState() == ITEM_STATE_VISIBLE) {
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
	}

}

void RestoreBlood::onPlayerContact()
{
	ScoreBar::getInstance()->restoreHealth();
}

RestoreBlood::RestoreBlood()
{
}

RestoreBlood::~RestoreBlood()
{
}