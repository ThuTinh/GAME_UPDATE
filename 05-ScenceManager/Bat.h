#pragma once
#include"Enemy.h"
class Bat : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Bat();
	~Bat();

private:

};

