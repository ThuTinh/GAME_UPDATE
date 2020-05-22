#include "SubBoomerangAttack.h"
#include"Simon.h"
#include"ScoreBar.h"
void SubBoomerangAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	SubWeaponAttack::Update(dt, coObjects);

}

void SubBoomerangAttack::Render()
{
	if (isAlive)
		animation_set->at(INDEX)->Render(x, y, frameIndex, direction);
}


SubBoomerangAttack::SubBoomerangAttack()
{
	setVy(0);
	setVx(VX);
	animation_set = CAnimationSets::GetInstance()->Get(ANI);

}

SubBoomerangAttack::~SubBoomerangAttack()
{
}