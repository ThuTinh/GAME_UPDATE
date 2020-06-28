#pragma once
#include"Enemy.h"

#define FLEAMAN_VY_SHORT 0.02
#define FLEAMAN_VY_LONG 0.09
#define FLEAMAN_VY_WHEN_JUMB 0.002
#define FLEAMAN_VX_WHEN_JUM 1
#define FLEAMAN_VX 0.02
#define FLEAMAN_GRAVITY -0.003
#define FLEAMAN_JUMBLONG_COUNTER 1
#define FLEAMAN_FUMBSHORT_COUNTER 2
#define FLEAMAN_DISTANCE_TO_JUMB 80
#define FLEAMAN_DISTANCE_STOP 20
#define FLEAMAN_SCORE 300


enum FLEAMAN_STATE {
	FLEAMAN_STATE_TO_JUMB,
	FLEAMAN_STATE_JUMP_SHORT,
	FLEAMAN_STATE_JUMP_LONG
};
enum FLEAMAN_ACTION {
	FLEAMAN_ACTION_STAND,
	FLEAMAN_ACTION_ATTACK
};
class Fleaman : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Fleaman();
	~Fleaman();

private:
	FLEAMAN_STATE fleamanState;
	int jumpRemain;

};

