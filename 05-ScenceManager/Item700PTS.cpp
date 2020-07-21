#include "Item700PTS.h"
#include"Simon.h"
#include"ScoreBar.h"
#include "money-effect.h"
#include "Game.h"
void Item700PTS::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		//MoneyEffect* effect = new MoneyEffect();
		//CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(effect);
		//effect->setX(getMidX());
		//effect->setY(getMidY());
		//effect->setAlive(true);
		//effect->aniIndex = 2;
		//effect->timeDelay.start();
		onPlayerContact();
		makeMoneyEffect(2);
	}
}

void Item700PTS::onPlayerContact()
{
	ScoreBar::getInstance()->increaseScore(ITEM700PTS_SCORE);
}

Item700PTS::Item700PTS()
{
}

Item700PTS::~Item700PTS()
{
}