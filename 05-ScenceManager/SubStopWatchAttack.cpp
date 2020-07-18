#include "SubStopWatchAttack.h"
#include"Simon.h"
#include"ScoreBar.h"
#include "Game.h"
void SubStopWatchAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	timeDelay.update();

	if (timeDelay.isTerminated())
	{
		CGame::GetInstance()->GetCurrentScene()->setStopUpdate(false);
		setAlive(false);
	}



}

void SubStopWatchAttack::Render()
{

}

SubStopWatchAttack::SubStopWatchAttack()
{
	
}

SubStopWatchAttack::~SubStopWatchAttack()
{
}