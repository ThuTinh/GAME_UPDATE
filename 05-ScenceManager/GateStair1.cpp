#include"GateStair1.h"
#include"Simon.h"
#include"Game.h"
#include"Camera.h"
#include"PlayScence.h"
void GateStair1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (AABBCheck(Simon::getInstance())) {
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->setCurentSpace(1);
	}
}

void GateStair1::Render()
{
}

GateStair1::GateStair1()
{

}

GateStair1::~GateStair1()
{
}