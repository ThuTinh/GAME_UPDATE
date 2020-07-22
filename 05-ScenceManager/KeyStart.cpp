#include "Gound.h"
#include "KeyStart.h"
#include"Simon.h"
#include "Game.h"

void KeyStart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	delayAni.update();
 	if (CGame::GetInstance()->isStartGame) {
		delayAni.start();
	}

	if (delayAni.isOnTime()) {
		if (timeAni.atTime())
		{
			isRender = true;
		}
		else
		{
			isRender = false;
		}
	}
  	if (delayAni.isTerminated()) {
		Simon::getInstance()->SetState(SIMON_STATE_INTRO);
		CGame::GetInstance()->SwitchScene(0);
		ScoreBar::getInstance()->setCurrentStageNumber(1);
	}
}

void KeyStart::Render()
{
	if (isRender)
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
}

KeyStart::KeyStart()
{
	setPhysicsEnable(false);
	delayAni.init(500);
	timeAni.init(40);
	isRender = true;
	setAlive(true);
}

void KeyStart::SetState(int state)
{
}
