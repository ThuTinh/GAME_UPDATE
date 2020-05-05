#include"GateStairChangeDirection.h"
#include"Simon.h"
#include"Game.h"
#include"Camera.h"
#include"PlayScence.h"
void GateStairChangeDirection::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (AABBCheck(Simon::getInstance())) {
		if (Simon::getInstance()->getState() == SIMON_STATE_ON_STAIR && Simon::getInstance()->getDy() > 0 && checkOnlyOne) {
			Simon::getInstance()->setStairDirection(1);
			checkOnlyOne = false;
		}
	}
}

void GateStairChangeDirection::Render()
{
}

GateStairChangeDirection::GateStairChangeDirection()
{
	checkOnlyOne = true;
}

GateStairChangeDirection::~GateStairChangeDirection()
{
}