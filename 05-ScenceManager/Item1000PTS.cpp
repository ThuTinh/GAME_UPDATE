#include "Item1000PTS.h"
#include"Simon.h"
#include"Gound.h"
#include"ScoreBar.h"
#include "Game.h"
#include "money-effect.h"
void Item1000PTS::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (getItemState() == ITEM_STATE_PLAYER_EATED || !getAlive())
		return;
	else
	{
		if (Simon::getInstance()->getX() - getX() > 30 && CGame::GetInstance()->current_scene == 1) {
			setItemState(ITEM_STATE_VISIBLE);
			setPhysicsEnable(true);
		}
		Item::Update(dt,coObjects);
			/* mặc định là false cho tới khi chạm sàn */
		if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
			setItemState(ITEM_STATE_PLAYER_EATED);
			setAlive(false);
			MoneyEffect* effect = new MoneyEffect();
			CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(effect);
			effect->setX(getMidX()+10);
			effect->setY(getMidY()+10);
			effect->setAlive(true);
			effect->aniIndex = 3;
			effect->timeDelay.start();
			onPlayerContact();
		}
	}
}

void Item1000PTS::onPlayerContact()
{
	ScoreBar::getInstance()->increaseScore(ITEM1000PTS_SCORE);
}

void Item1000PTS::Render()
{
	if (getItemState() == ITEM_STATE_VISIBLE) {
		animation_set->at(1)->Render(x, y, frameIndex, DIRECTION_LEFT);
	}
}

Item1000PTS::Item1000PTS()
{
	setPhysicsEnable(false);
}

Item1000PTS::~Item1000PTS()
{
}
