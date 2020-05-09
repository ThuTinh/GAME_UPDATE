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
	setX(getX() + nx*0.2);
	
}

void GiaDo::Render()
{
	animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
}

GiaDo::GiaDo()
{
	nx = 1;
}
