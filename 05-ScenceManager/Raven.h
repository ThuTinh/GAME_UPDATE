#pragma once
#include"Enemy.h"
class Raven : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Raven();
	~Raven();

private:

};

