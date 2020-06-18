#pragma once
#include"Enemy.h"
#define BAT_RUN_DX 85
#define BAT_VX 0.05
#define BAT_VY -0.08
#define BAT_SCORE 200
#define DISTACE_CHANGE_FLY_HORIZONTAL 40
enum BAT_ACTION {
	BAT_ACTION_STAND,
	BAT_ACTION_FLY
};
enum BAT_SATE {
	BAT_STATE_STAND,
	BAT_STATE_FLY
};
class Bat : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int distanceNeedFlyHorizonal;
	Bat();
	~Bat();

private:

};

