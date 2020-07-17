#pragma once
#include"Enemy.h"
#define GHOST_SCORE 200
#define DISTANCE_X 60
#define GHOST_DISTANCE_STOP 40
#define VX_GHOST 0.02
#define GHOST_GRAVITY -0.003
#define COUNTER_LIFE 2
enum GHOST_STATE {
	GHOST_STATE_STAND,
	GHOST_STATE_ATTACK
};
enum GHOST_ACTION {
	GHOST_ACTION_STAND,
	GHOST_ACTION_FLY
};
class Ghost : public Enemy
{
	bool isRender;
	DelayTime timeDelay;
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

