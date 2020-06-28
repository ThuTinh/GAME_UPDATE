#include "WhiteBone.h"
#include"Simon.h"
#include"ScoreBar.h"
void WhiteBone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timeDelay.update();
	vy += WHITE_BONE_GRAVITY * dt;
	setDirectionFollowPlayer();
	if (timeCheck.atTime())
	{
		if (isAlive) {
			if (AABBCheck(Simon::getInstance())) {
				ScoreBar::getInstance()->increaseHealth(-1);
			}
		}
	}
	if (timeDelay.isTerminated()) {
		setAlive(false);
	}
	CGameObject::Update(dt, coObjects);
	setX(getDirection()*  getDx() + getX());
	setY(getDy() + getY());  


}

void WhiteBone::Render()
{
	if (isAlive)
		animation_set->at(0)->Render(x, y, frameIndex, direction);
}

void WhiteBone::setDirectionFollowPlayer()
{
	if (Simon::getInstance()->getMidX() - getMidX() < 0)
	{
		setDirection(DIRECTION_LEFT);
	}
	else
	{
		setDirection(DIRECTION_RIGHT);
	}
}

WhiteBone::WhiteBone()
{
	setVx(VX);
	setVy(VY);
	timeDelay.init(TIME_DELAY);
	timeCheck.init(TIME_DELAY);
	animation_set = CAnimationSets::GetInstance()->Get(WHITE_BONE_ANI);


}

WhiteBone::~WhiteBone()
{
}