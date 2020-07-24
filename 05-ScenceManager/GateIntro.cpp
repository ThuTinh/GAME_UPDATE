#include"GateIntro.h"
#include"Simon.h"
#include"Game.h"
#include"Camera.h"
#include"ScoreBar.h"
void GateIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	delayWait.update();
	if (AABBCheck(Simon::getInstance())) {
		if (!CheckOnlyOne) {
			Simon::getInstance()->SetState(SIMON_STATE_INTRO_AWAIT);
			delayWait.start();
			CheckOnlyOne = true;
		}
		
	}
	if (delayWait.isTerminated()) {
		Simon::getInstance()->SetState(SIMON_STATE_NORMAL);
		CGame::GetInstance()->SwitchScene(1);
		ScoreBar::getInstance()->setCurrentStageNumber(1);
	}
}

void GateIntro::Render()
{
}

GateIntro::GateIntro()
{
	delayWait.init(1000);
	CheckOnlyOne = false;
	setCollitionType(COLLISION_TYPE_MISC);

}

GateIntro::~GateIntro()
{
}