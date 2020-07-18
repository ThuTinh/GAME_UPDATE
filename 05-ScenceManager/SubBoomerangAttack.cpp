#include "SubBoomerangAttack.h"
#include"Simon.h"
#include"ScoreBar.h"
#include "Camera.h"
void SubBoomerangAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	SubWeaponAttack::Update(dt, coObjects);
	if (getX() >= Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) {
		setVx(-VX);

	}
	if ( Camera::getInstance()->getX() > getX()) {
		setVx(VX);
	}
	
	if (!timeCheckSimon.isOnTime()) {
		if (AABBCheck(Simon::getInstance())) {
			if(isAlive)
				ScoreBar::getInstance()->increaseHeartCount(1);
			setAlive(false);
		}
	}
	
}

void SubBoomerangAttack::Render()
{
	if (isAlive)
		animation_set->at(INDEX)->Render(x, y, frameIndex, direction);
}


SubBoomerangAttack::SubBoomerangAttack()
{
	setVy(0);
	animation_set = CAnimationSets::GetInstance()->Get(ANI);

}

SubBoomerangAttack::~SubBoomerangAttack()
{
}