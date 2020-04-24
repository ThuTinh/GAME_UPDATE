#pragma once
#include "GameObject.h"
#include"DelayTime.h"

#define SIMON_VX	0.04 
//0.1f
#define SIMON_JUMP_Y		0.25f

#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			-0.0008f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_NORMAL 100
#define SIMON_STATE_ON_STAIR 101
#define SIMON_STATE_ATTACK 102
#define SIMON_STATE_ATTACK_JUMP 103
#define SIMON_STATE_DIE 104

#define SIMON_STAIR_STATE_NORUN 200
#define SIMON_STAIR_STATE_GO_UP 201
#define SIMON_STAIR_STATE_GO_DOWN 202

#define SIMON_ANI_STAND 0
#define SIMON_ANI_GO	1
#define SIMON_ANI_JUMB	2
#define SIMON_ANI_ASCEND_STAIRS	3
#define SIMON_ANI_DESCEN_STAIRS	4
#define SIMON_ANI_HURT	5
#define SIMON_ANI_DEAD	6
#define SIMON_ANI_INTRO	7
#define SIMON_ANI_STAND_USING_SUB	8
#define SIMON_ANI_DUCK_USING_SUB	9
#define SIMON_ANI_ASCEN_STAIRS_USING_SUB 10	
#define SIMON_ANI_DESCEN_STAIRS_USING_SUB 11
#define SIMON_ANI_COLORS 12




class Simon : public CGameObject
{
	int level;
	static Simon* instance;

public: 
	bool isRightDown;
	bool isLeftDown;
	bool isUpDown;
	bool isDownDown;
	bool isJumpDown;
	bool isAttack;
	//bool isPreviousUpDown,
	//	isUpPress,
	//	isPreviousDownDown,
	//	isDownPress,
	//	isPreviousJumpDown,
	//	isJumpPress,
	//	isPreviousAttackDown,
	//	isAttackPress;
	int numberArchery;
	DelayTime attachDelay;
	DelayTime colorDelay;
	Simon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void setNumberArchery(int num);
	int getNumberArchery();
	void addNumberArchery(int num);
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	static Simon* getInstance();
	void onCollision(CGameObject* other, float collisionTime, int nx, int ny) override;
	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};