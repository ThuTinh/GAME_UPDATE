#pragma once
#include"Enemy.h"
#define BAT_RUN_DX 80
#define BAT_VX 0.1
#define BAT_VY -0.03
#define BAT_SCORE 200

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
	Bat();
	~Bat();

private:

};

