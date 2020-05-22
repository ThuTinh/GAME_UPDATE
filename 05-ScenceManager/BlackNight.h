#pragma once
#include"Enemy.h"

#define BLACKNIGHT_VX 0.03
#define BLACKNIGHT_SCORE 400
#define COUNTER_LIFE 2
class BlackNight : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	 void onCollision(CGameObject* other, float collisionTime, int nx, int ny) override;
	virtual void Render();
	int counterInjured;
	BlackNight();
	~BlackNight();

private:

};

