#pragma once
#include"Enemy.h"
#define RAVEN_SCORE 200
#define DISTANCE_X 70
#define RAVEN_DISTANCE_STOP 10
#define RAVEN_VX 0.035
#define RAVEN_VY 0.005
#define RAVEN_GRAVITY -0.0005
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
	float xDes, yDes;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void calculateOtherPoint();
	Raven();
	~Raven();

private:

};

