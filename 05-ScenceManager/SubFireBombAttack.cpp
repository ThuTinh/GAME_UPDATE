#include "SubFireBombAttack.h"
#include"Simon.h"
#include"ScoreBar.h"
void SubFireBombAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void SubFireBombAttack::Render()
{
	if (isAlive)
		animation_set->at(INDEX)->Render(x, y, frameIndex, direction);
}

SubFireBombAttack::SubFireBombAttack()
{
	setVy(VY_AXE);
	setVx(VX_AXE);
	timeDelay.init(TIME_DELAY_AXE);
	setDirectionFollowPlayer();
	animation_set = CAnimationSets::GetInstance()->Get(ANI);

}

SubFireBombAttack::~SubFireBombAttack()
{
}