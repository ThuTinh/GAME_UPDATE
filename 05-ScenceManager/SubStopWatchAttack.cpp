#include "SubStopWatchAttack.h"
#include"Simon.h"
#include"ScoreBar.h"
void SubStopWatchAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	timeDelay.update();
	vy += AXE_GRAVITY * dt;
	if (timeDelay.isTerminated())
	{
		setAlive(false);
	}
	CGameObject::Update(dt, coObjects);
	setX(getDx() + getX());
	setY(getDy() + getY());

}

void SubStopWatchAttack::Render()
{
	if (isAlive)
		animation_set->at(INDEX)->Render(x, y, frameIndex, direction);
}

SubStopWatchAttack::SubStopWatchAttack()
{
	setVy(VY_AXE);
	setVx(VX_AXE);
	timeDelay.init(TIME_DELAY_AXE);
	setDirectionFollowPlayer();
	animation_set = CAnimationSets::GetInstance()->Get(ANI);

}

SubStopWatchAttack::~SubStopWatchAttack()
{
}