#pragma once
#include"Enemy.h"
#define RAVEN_SCORE 200
#define DISTANCE_X 60
#define VX 0.02
#define VY 0.0003
#define RAVEN_GRAVITY -0.003
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

