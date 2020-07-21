#include "SmallHeart.h"
#include"Simon.h"
#include"ScoreBar.h"
void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		onPlayerContact();
	}
}

void SmallHeart::Render()
{
	if (getItemState() == ITEM_STATE_VISIBLE) {
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
	}
}

void SmallHeart::onPlayerContact()
{
	ScoreBar::getInstance()->increaseHeartCount(NUMBER_HEART);
}

SmallHeart::SmallHeart()
{
}

SmallHeart::~SmallHeart()
{
}