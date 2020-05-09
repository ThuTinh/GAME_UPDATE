#include"GateStair.h"
#include"Simon.h"
#include"Game.h"
#include"Camera.h"
#include"PlayScence.h"
void GateStair::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (AABBCheck(Simon::getInstance())) {
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->setCurentSpace(1);
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