#pragma once
#include"Enemy.h"
class Zoombie : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Zoombie();
	~Zoombie();

private:

};

