#pragma once
#include"Enemy.h"
class BlackNight : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	BlackNight();
	~BlackNight();

private:

};

