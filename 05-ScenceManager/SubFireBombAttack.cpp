#include "SubFireBombAttack.h"
#include"Simon.h"
#include"ScoreBar.h"
#include "explore-effect.h"
#include "Game.h"
void SubFireBombAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	timeDelay.update();
	vy += AXE_GRAVITY * dt;
	if (timeDelay.isTerminated())
	{
		Simon::getInstance()->canMakeSub = true;
		setAlive(false);
		ExploreEffect *effect = new ExploreEffect();
		CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(effect);
		effect->setX(getMidX());
		effect->setY(getMidY() + 25);
		effect->setAlive(true);
		effect->setPhysicsEnable(true);
		effect->timeDelay.start();
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