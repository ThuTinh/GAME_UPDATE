#include "Gound.h"
#include "KeyStart.h"
#include "Weapon.h"
#include"Simon.h"
#include "Die-affect.h"
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
			setAlive(true);
		}
		else
		{
			setAlive(false);
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
	if (isAlive)
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
}

KeyStart::KeyStart()
{
	setPhysicsEnable(false);
	delayAni.init(200);
	timeAni.init(30);
}

void KeyStart::SetState(int state)
{
}
