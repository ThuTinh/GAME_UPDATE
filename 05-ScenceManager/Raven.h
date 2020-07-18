#pragma once
#include"Enemy.h"
#define RAVEN_SCORE 200
#define DISTANCE_X 70
#define RAVEN_DISTANCE_STOP 10
#define VX 0.025
#define VY 0.004
#define RAVEN_GRAVITY -0.00055
enum RAVEN_STATE {
	RAVEN_STATE_STAND,
	RAVEN_STATE_ATTACK
};
enum RAVEN_ACTION {
	RAVEN_ACTION_STAND,
	RAVEN_ACTION_FLY
};
class Raven : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Raven();
	~Raven();

private:

};

