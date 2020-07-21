#pragma once
#include"Enemy.h"
#include"DelayTime.h"
#include "Simon.h"
#include "IBoss.h"
#define Boss_time_wait 1000
#define boss_distance_activ 50
#define vampire_bat_fast_momen 150
#define boss_move_fast_time_min 1000
#define boss_move_fast_time_max 2000
#define boss_move_slow_time_min	1000
#define boss_move_slow_time_max 2000
enum BOSS_STATE
{
	BOSS_STATE_INVISIBLE,
	BOSS_STATE_WAIT,
	BOSS_STATE_MOVE_FAST,
	BOSS_STATE_MOVE_SLOW
};

enum BOSS_ACTION
{
	BOSS_ACTION_WAIT,
	BOSS_ACTION_ACTIV
};

class BossBat : public Enemy, public IBoss
{
public:
	BOSS_STATE bossState;
	Simon* player;
	DelayTime waitDelay;
	DelayTime moveFastDelay;
	DelayTime moveSlowDelay;
	DelayTime hurtDelay;
	float xDes, yDes;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	//void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setBossState(BOSS_STATE bossState);
	void calculateOtherPoint();
	void checkWithSimon();
	void onDecreaseHealth();
	void makeDieEffect() override;
	void restore();

	void preventGoOutsideCamera();
	BossBat();
	~BossBat();

private:

};

