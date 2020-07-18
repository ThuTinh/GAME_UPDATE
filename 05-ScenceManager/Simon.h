#pragma once
#include "GameObject.h"
#include"DelayTime.h"
#include "GameTime.h"
#include "Item.h"
#include "ScoreBar.h"
#define SIMON_VX	0.08
//0.1f
#define SIMON_JUMP_Y		0.25f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			-0.0007f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_NORMAL 100
#define SIMON_STATE_ON_STAIR 101
#define SIMON_STATE_ATTACK_STAND 102
#define SIMON_STATE_ATTACK_JUMP 103
#define SIMON_STATE_DIE 104
#define SIMON_STATE_HURT 105
#define SIMON_STATE_DUCK 106
#define SIMON_STATE_ATTACK_DUCK 107
#define SIMON_STATE_USE_SUB 108
#define SIMON_STAIR_STATE_NORUN 200
#define SIMON_STAIR_STATE_GO_UP 201
#define SIMON_STAIR_STATE_GO_DOWN 202
#define SIMON_STAIR_STATE_ATTACK_ASCEN 203 // len cau thang
#define SIMON_STAIR_STATE_ATTACK_DESEN 204


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
	int playerStairDestx, playerStairDesty;
	int playerStairState;
	int stairDirection;
	/* là lần di chuyển cuối cùng của player. sau khi di chuyển player sẽ thoát khỏi stair  */
	bool isLastRunStair;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
public: 
	Item *subWeapon;
	bool isRightDown;
	bool isLeftDown;
	bool isUpDown;
	bool isDownDown;
	bool isJumpDown;
	bool isPreviousJumpDown;
	bool isJump;
	bool isAttack;
	bool isAttackDown;
	bool switchScene1;
	bool switchScene2;
	bool switchScene3;
	bool switchScene4;
	bool isPreviousAttackDown;
	int numberArchery;
	int fixWidth;
	int fixHeight;
	int numberObjectBlack;
	bool isUseSub;
	bool renderActive;
	int hurtDirection;
	bool isOnGiaDo;
	DelayTime attackStandDelay;
	DelayTime colorDelay;
	DelayTime hurtDelay;
	DelayTime deadDelay;
	DelayTime duckDelay;
	//DelayTime jumbDelay;
	DelayTime attackDuckDelay;
	DelayTime attacJumbDelay;
	DelayTime attackUseSub;
	GameTime blinkTime;
	DelayTime hideHurtDelay;
	DelayTime attackInStairDelay;
	DelayTime hurtTimeDelay;
	GameTime hurtTime;
	DelayTime jumbHurtTimeDelay;
	bool switchSceneIn;
	static Simon* instance;
	static Simon* getInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void retoreWidthHeight();
	Item *getSubweapon();
	void setSubWeapon(Item * item);
	void setNumberArchery(int num);
	void addNumberObjectBlack(int num);
	int getNumberObjectBlack();
	void setNumberObjectBlack(int init);
	int getNumberArchery();
	void addNumberArchery(int num);
	void SetState(int state);
	int getState();
	void makeSubWeapon(TYPE_SUBWEAPON type);
	void setAnChorRight();
	void setAnChorLeft();
	void SetLevel(int l) { level = l; }
	void setStartStair();
	void setStopStair();
	bool getIsLastRunStair();
	void setIsLastRunStair(bool isLastRunStair);
	void goStairUp();
	void goStairDown();
	void setStairDirection(int stairDirection);
	void setPlayerStairState(int playerStairState);
	void setRenderActive(bool renderActive);
	bool getRenderActive();
	void onCollision(CGameObject* other, float collisionTime, int nx, int ny) override;
	void Load(LPCWSTR simonFile);

	void setHurt(int directEnemy, float xOfEnemy);
	bool isDie();
	Simon();

};