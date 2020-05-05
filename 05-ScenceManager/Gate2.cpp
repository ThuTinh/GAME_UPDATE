#include"Gate2.h"
#include"Simon.h"
#include"Game.h"
#include"Camera.h"
#include"ScoreBar.h"
void Gate2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (AABBCheck(Simon::getInstance())) {
		CGame::GetInstance()->SwitchScene(CGame::GetInstance()->current_scene + 1);
		ScoreBar::getInstance()->setCurrentStageNumber(ScoreBar::getInstance()->getCurrentStageNumber() + 1);

	}
}

void Gate2::Render()
{
}

Gate2::Gate2()
{

}

Gate2::~Gate2()
{
}