#include "SubFireBombAttack.h"
#include"Simon.h"
#include"ScoreBar.h"
#include "explore-effect.h"
#include "Game.h"
#include "Gound.h"
void SubFireBombAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	timeDelay.update();
	vy += AXE_GRAVITY * dt;
	CGameObject::Update(dt, coObjects);
	setX(getDx() + getX());
	setY(getDy() + getY());
	//Tính va cham voi ground de tao hieu ứng
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	// turn off collision when die 
	if (isAlive)
		CalcPotentialCollisions(coObjects, coEvents);
	// No collision occured, proceed normally
	if (coEvents.size() != 0)
	{
		// TODO: This is a very ugly designed function!!!!
		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (dynamic_cast<Ground*>(e->obj)) {
				ExploreEffect* effect = new ExploreEffect();
				CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(effect);
				effect->setX(getMidX());
				effect->setY(e->obj->getY()+15);
				effect->setAlive(true);
				effect->setPhysicsEnable(true);
				effect->timeDelay.start();
				Simon::getInstance()->canMakeSub = true;
				setAlive(false);
			}
			
		}
	}
	else
	{
		if (timeDelay.isTerminated())
		{
			Simon::getInstance()->canMakeSub = true;
			setAlive(false);
		}
	}
	//clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	/* mặc định là false cho tới khi chạm sàn */
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
	timeDelay.init(TIME_DELAY_FRIE_BOOM);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	setDirectionFollowPlayer();
	setPhysicsEnable(true);
	animation_set = CAnimationSets::GetInstance()->Get(ANI);

}

SubFireBombAttack::~SubFireBombAttack()
{
}