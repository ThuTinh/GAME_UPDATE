#pragma once
#include"Enemy.h"

#define BLACKNIGHT_VX 0.02
#define BLACKNIGHT_SCORE 500
class BlackNight : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	BlackNight();
	~BlackNight();

private:

};

