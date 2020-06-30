#pragma once
#include"Enemy.h"
#define GHOST_SCORE 200
#define DISTANCE_X 60
#define GHOST_DISTANCE_STOP 10
#define VX 0.015
#define GHOST_GRAVITY -0.003
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
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void setIsRender(bool render);
	bool getIsRender();
	Ghost();
	~Ghost();

private:

};

