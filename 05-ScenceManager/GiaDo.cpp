#include "GiaDo.h"
#include"GameObject.h"

void GiaDo::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (getX()+ width >= MAX_X) {
		nx = -1;
	}
	if (getX() <= MIN_X) {
		nx = 1;
	}
	setVx(nx * Vx);
	setX(getX() + getVx()*dt);
}

void GiaDo::Render()
{
	animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
}

GiaDo::GiaDo()
{
	setVx(Vx);
	nx = 1;
}
