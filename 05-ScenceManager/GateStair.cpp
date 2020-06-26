#include"GateStair.h"
#include"Simon.h"
#include"Game.h"
#include"Camera.h"
#include"PlayScence.h"
void GateStair::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (AABBCheck(Simon::getInstance()) && Simon::getInstance()->getState() == SIMON_STATE_ON_STAIR && Simon::getInstance()->aniIndex == SIMON_ANI_ASCEND_STAIRS) {
		if (dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->getCurentSpace() == dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->spaces[1])
			return;
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->setCurentSpace(1);
	}
	if (AABBCheck(Simon::getInstance()) && Simon::getInstance()->getState() == SIMON_STATE_ON_STAIR && Simon::getInstance()->aniIndex == SIMON_ANI_DESCEN_STAIRS) {
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->setCurentSpace(2);
	}
}

void GateStair::Render()
{
}

GateStair::GateStair()
{

}

GateStair::~GateStair()
{
}