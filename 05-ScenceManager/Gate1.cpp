#include"Gate1.h"
#include"Simon.h"
#include"Game.h"
#include"Camera.h"
#include"ScoreBar.h"
void Gate1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (AABBCheck(Simon::getInstance())) {
		CGame::GetInstance()->SwitchScene(2);
		ScoreBar::getInstance()->setCurrentStageNumber(ScoreBar::getInstance()->getCurrentStageNumber() + 1);
		
	}
}

 void Gate1::Render()
{
}

Gate1::Gate1()
{
	
}

Gate1::~Gate1()
{
}