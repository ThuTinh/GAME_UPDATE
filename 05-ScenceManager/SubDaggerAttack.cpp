#include "SubDaggerAttack.h"
#include"Simon.h"
#include"ScoreBar.h"
void SubDaggerAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	SubWeaponAttack::Update(dt, coObjects);

}

void SubDaggerAttack::Render()
{
	if(isAlive)
		animation_set->at(INDEX)->Render(x, y, frameIndex, direction);
}


SubDaggerAttack::SubDaggerAttack()
{
	setVy(0);
	setVx(VX);
	animation_set = CAnimationSets::GetInstance()->Get(ANI);

}

SubDaggerAttack::~SubDaggerAttack()
{
}