#include"GateStair2.h"
#include"Simon.h"
#include"Game.h"
#include"Camera.h"
#include"PlayScence.h"
void GateStair2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (AABBCheck(Simon::getInstance())) {
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->setCurentSpace(1);
	}
}

void GateStair2::Render()
{
}

GateStair2::GateStair2()
{

}

GateStair2::~GateStair2()
{
}