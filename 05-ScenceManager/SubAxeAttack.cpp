#include "SubAxeAttack.h"
#include"Simon.h"
#include"ScoreBar.h"
void SubAxeAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	SubWeaponAttack::Update(dt, coObjects);

}

void SubAxeAttack::Render()
{
	if (isAlive)
		animation_set->at(INDEX)->Render(x, y, frameIndex, direction);
}

SubAxeAttack::SubAxeAttack()
{
	setVy(0);
	setVx(VX);
	animation_set = CAnimationSets::GetInstance()->Get(ANI);

}

SubAxeAttack::~SubAxeAttack()
{
}