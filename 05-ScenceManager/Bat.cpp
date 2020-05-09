#include "Bat.h"
#include"Gound.h"
#include"Simon.h"
void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	switch (state)
	{
	case BAT_STATE_STAND:
		setDx(0);
		setDy(0);
		if (Simon::getInstance()->getX() > getX() && Simon::getInstance()->getX() - getX() < BAT_RUN_DX &&  abs(Simon::getInstance()->getY() - getY() )<80 )
		{
			state = BAT_STATE_FLY;
			setPhysicsEnable(true);
			setVy(BAT_VY);
			setVx(BAT_VX);
			aniIndex = BAT_ACTION_FLY;
		}
		break;
	case BAT_STATE_FLY:
		break;
	default:
		break;
	}
	x += dx;
	y += dy;
	CGameObject::Update(dt);
}

void Bat::Render()
{
	animation_set->at(aniIndex)->Render(x, y, frameIndex, direction);
}

Bat::Bat()
{
	setPhysicsEnable(false);
	setCollitionType(COLLISION_TYPE_ENEMY);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	setPhysicsEnable(true);
	setVx(0.03);
	setPhysicsEnable(false);
	aniIndex = BAT_ACTION_STAND;
	state = BAT_STATE_STAND;
}

Bat::~Bat()
{
}