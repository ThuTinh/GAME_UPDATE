#pragma once
#include"Enemy.h"
#include "DelayTime.h"
#define RAVEN_SCORE 200
#define DISTANCE_X 80
#define RAVEN_DISTANCE_STOP 10
#define RAVEN_VX 0.025
#define RAVEN_GRAVITY -0.0005
#define TIME_AWAIT 1000
#define TIME_ATTACK 1200
enum RAVEN_STATE {
	RAVEN_STATE_STAND,
	RAVEN_STATE_ATTACK,
	RAVEN_STATE_WAIT
};
enum RAVEN_ACTION {
	RAVEN_ACTION_STAND,
	RAVEN_ACTION_FLY
};
class Raven : public Enemy
{
	float xDes, yDes;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void calculateOtherPoint();
	DelayTime delayTimeWait;
	DelayTime delayTimeAttack;
	Raven();
	~Raven();

private:

};

