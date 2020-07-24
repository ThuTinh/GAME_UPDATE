#pragma once
#include"Enemy.h"
#define GHOST_SCORE 200
#define DISTANCE_X 60
#define GHOST_DISTANCE_STOP 40
#define VX_GHOST 0.02
#define VY_GHOST 0.01
#define GHOST_GRAVITY -0.003
#define COUNTER_LIFE 2
#define COUNTER_LIFE_NOMAL 3
enum GHOST_STATE {
	GHOST_STATE_STAND,
	GHOST_STATE_ATTACK,
	GHOST_STATE_HURT

};
enum GHOST_ACTION {
	GHOST_ACTION_STAND,
	GHOST_ACTION_FLY,
};
class Ghost : public Enemy
{
	bool isRender;
	DelayTime timeDelay;
	DelayTime timeHurtDelay;
	int counterInjured;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void setIsRender(bool render);
	bool getIsRender();
	Ghost();
	~Ghost();

private:

};

