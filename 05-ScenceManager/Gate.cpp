#include"Gate.h"
#include"Simon.h"
#include"Game.h"
#include"Camera.h"
#include"ScoreBar.h"
void Gate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (AABBCheck(Simon::getInstance())) {
		CGame::GetInstance()->SwitchScene(CGame::GetInstance()->current_scene + 1);
		ScoreBar::getInstance()->setCurrentStageNumber(ScoreBar::getInstance()->getCurrentStageNumber() + 1);
	}
}

void Gate::Render()
{
}

Gate::Gate()
{
	setCollitionType(COLLISION_TYPE_MISC);
}

Gate::~Gate()
{
}