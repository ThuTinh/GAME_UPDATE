#include <algorithm>
#include <fstream>
#include <assert.h>
#include "Utils.h"
#include "Simon.h"
#include "Game.h"
#include "Gound.h"
#include "Textures.h"
#include "ScoreBar.h"
#include "Weapon.h"
#include "Enemy.h"
#include "GiaDo.h"
#include "SubDaggerAttack.h"
#include "SubBoomerangAttack.h"
#include "SubWeaponAttack.h"
#include "SubAxeAttack.h"
#include "SubFireBombAttack.h"
#include "SubStopWatchAttack.h"
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_MAP	3
#define SCENE_SECTION_SPRITES 4
#define SCENE_SECTION_ANIMATIONS 5
#define SCENE_SECTION_ANIMATION_SETS 6
#define SCENE_SECTION_OBJECTS	7
#define SCENE_SECTION_SPACE	8
#define SCENE_SECTION_STAIR 9
#define MAX_SCENE_LINE 1024
Simon *Simon::instance = 0;

typedef vector<LPCOLLISIONEVENT> VectorType;

void Simon::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}
void Simon::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);


	if (tokens.size() < 10) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int x = atoi(tokens[1].c_str());
	int y = atoi(tokens[2].c_str());
	int with = atoi(tokens[3].c_str());
	int height = atoi(tokens[4].c_str());
	int anchorX = atoi(tokens[5].c_str());
	int anchorY = atoi(tokens[6].c_str());
	int anchorXRight = atoi(tokens[7].c_str());
	int anchorYRight = atoi(tokens[8].c_str());
	int texID = atoi(tokens[9].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, x, y, with, height, anchorX, anchorY, anchorXRight , anchorYRight ,tex);
}
void Simon::_ParseSection_ANIMATIONS(string line)
{

	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time
	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

LPGAMEOBJECT getMyObject(vector<LPGAMEOBJECT>* coo)
{
	for (size_t i = 0; i < coo->size(); i++)
	{
		if (coo->at(i)->getX() == 65)
		{
			return coo->at(i);
		}
	}
	return 0;
}

void Simon::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

Simon::Simon() : CGameObject()
{
	setPhysicsEnable(true);
	setRenderActive(true);
	setVx(0);
	setAlive(true);
	setDirection(DIRECTION_RIGHT);
	SetState(SIMON_STATE_NORMAL);
	setNumberArchery(0);
	isUseSub = false;
	attackStandDelay.init(400);
	attacJumbDelay.init(400);
	colorDelay.init(300);
	hurtDelay.init(100);
	deadDelay.init(200);
	duckDelay.init(200);
	attackUseSub.init(400);
	blinkTime.setDeltaTime(200);
	hideHurtDelay.init(50);
	attackInStairDelay.init(400);
	//jumbDelay.init(80);
	attackDuckDelay.init(400);
	setCollitionType(COLLISION_TYPE_PLAYER);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
//	collitionTypeToCheck.push_back(COLLISION_TYPE_ENEMY);


	hurtTimeDelay.init(1200);
	jumbHurtTimeDelay.init(250);
	hurtTime.init(45);
	canMakeSub = true;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	if (switchScene1) {
		CGame::GetInstance()->SwitchScene(1);
		ScoreBar::getInstance()->setCurrentStageNumber(1);

		return;
	}
	if (switchScene2) {
		CGame::GetInstance()->SwitchScene(2);
		ScoreBar::getInstance()->setCurrentStageNumber(2);
		return;
	}
	if (switchScene3) {
		CGame::GetInstance()->SwitchScene(3);
		ScoreBar::getInstance()->setCurrentStageNumber(3);

		return;
	}
	if (switchScene4) {
		CGame::GetInstance()->SwitchScene(4);
		ScoreBar::getInstance()->setCurrentStageNumber(4);

		return;
	}
	if (getY() < 0) {
		CGame::GetInstance()->SwitchScene(CGame::GetInstance()->current_scene);
		ScoreBar::getInstance()->setTypeSubWeapon(TYPE_SUBWEAPON::DEFAUL);
		return;
	}
	attackStandDelay.update();
	colorDelay.update();
	//hurtDelay.update();
	duckDelay.update();
	attacJumbDelay.update();
	attackDuckDelay.update();
	attackUseSub.update();
	//hideHurtDelay.update();
	hurtTimeDelay.update();
	deadDelay.update();
	attackInStairDelay.update();
	jumbHurtTimeDelay.update();
	isOnGiaDo = false;
	CGameObject::Update(dt);
	if (aniIndex == SIMON_ANI_COLORS) {
		
		if(colorDelay.isTerminated()) {
			aniIndex = SIMON_ANI_STAND;
			state = SIMON_STATE_NORMAL;
		}
		else
		{
			return;
		}
	}

	if (hurtTimeDelay.isOnTime())
	{
		isOnGround = true;
		if (hurtTime.atTime())
		{
			setRenderActive(false);
		}
		else
		{
			setRenderActive(true);
		}
	}

	if (hurtTimeDelay.isTerminated())
	{
		setRenderActive(true);
		ScoreBar::getInstance()->increaseHealth(-1);
		setStopCollision(false);
		setPhysicsEnable(true);
		state = SIMON_STATE_NORMAL;
		isOnGround = true;
	}
	
	if (!stopCollision) {
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		// turn off collision when die 
		if (isAlive)
			CalcPotentialCollisions(coObjects, coEvents);
		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			//// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
			if (rdx != 0 && rdx != dx)
				x += nx * abs(rdx);

			//block every object first!
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;
			//
			// Collision logic with other objects
			//
			for (UINT i = 0; i < coEvents.size(); i++)
			{
				LPCOLLISIONEVENT e = coEvents[i];
				if (dynamic_cast<Ground*>(e->obj)) {
					onCollision(e->obj, e->t, e->nx, e->ny);
					if (state == SIMON_STATE_HURT) {
						if (jumbHurtTimeDelay.isTerminated()) {
							//setPhysicsEnable(false);
							setStopCollision(true);
							aniIndex = SIMON_ANI_STAND;
							return;
						}
						if (jumbHurtTimeDelay.isOnTime()) {
							x += hurtDirection *0.7;
							y += 20;
							return;
						}
						
					}
				}
				if (dynamic_cast<GiaDo*>(e->obj)) {
					setVx(e->obj->getVx());
					isOnGiaDo = true;
					onCollision(e->obj, e->t, e->nx, e->ny);
				}
				
			}
		}

		//clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		/* mặc định là false cho tới khi chạm sàn */
	}
	
	// Simple fall down
	vy += MARIO_GRAVITY * dt;
	if (attackStandDelay.isTerminated())
	{
		state = SIMON_STATE_NORMAL;
		animation_set->at(SIMON_ANI_STAND_USING_SUB)->setCurrentFrame(-1);
	}
	
	if (attacJumbDelay.isTerminated())
	{
		state = SIMON_STATE_NORMAL;
		animation_set->at(SIMON_ANI_STAND_USING_SUB)->setCurrentFrame(-1);
	}
	if (attackDuckDelay.isTerminated())
	{
		state = SIMON_STATE_DUCK;
		animation_set->at(SIMON_ANI_DUCK_USING_SUB)->setCurrentFrame(-1);
	}
	if (attackUseSub.isTerminated()) {
		state = SIMON_STATE_NORMAL;
		animation_set->at(SIMON_ANI_STAND_USING_SUB)->setCurrentFrame(-1);
	}
	if (aniIndex == SIMON_ANI_ASCEN_STAIRS_USING_SUB || aniIndex == SIMON_ANI_DESCEN_STAIRS_USING_SUB)
	{
		if (attackInStairDelay.isTerminated())
		{
			playerStairState = SIMON_STAIR_STATE_NORUN;
			if (aniIndex == SIMON_ANI_DESCEN_STAIRS_USING_SUB)
			{
				aniIndex = SIMON_ANI_DESCEN_STAIRS;
				animation_set->at(SIMON_ANI_DESCEN_STAIRS_USING_SUB)->setCurrentFrame(-1);
			}
			else
			{
				aniIndex = SIMON_ANI_ASCEND_STAIRS;
				animation_set->at(SIMON_ANI_ASCEN_STAIRS_USING_SUB)->setCurrentFrame(-1);
			}
		}
		else
		{
			return;
		}

	}
	
	isUseSub = false;
	switch (state)
	{
	case SIMON_STATE_NORMAL: {
		if (isOnGround) {
			if (isRightDown) {
				setDirection(DIRECTION_RIGHT);
				aniIndex = SIMON_ANI_GO;
				setVx(SIMON_VX);
			}
			else
			{
				if (isLeftDown) {
					aniIndex = SIMON_ANI_GO;
					setDirection(DIRECTION_LEFT);
					setVx(-SIMON_VX);
				}
				else
				{
					if (isDownDownPress) {
						state = SIMON_STATE_DUCK;
						setHeight(25);
						duckDelay.start();
					}
					else
					{
						if (isUpDown) {
							if (isAttack)    {
								if (ScoreBar::getInstance()->getHeartCount() <= 0 || ScoreBar::getInstance()->getTypeSubWeapon() == DEFAUL || !canMakeSub){
									state = SIMON_STATE_ATTACK_STAND;
									setVx(0);
									attackStandDelay.start();
								}
								else
								{
									
										state = SIMON_STATE_USE_SUB;
										attackUseSub.start();
										makeSubWeapon(ScoreBar::getInstance()->getTypeSubWeapon());
									
									
								}
							}
							else {

								aniIndex = SIMON_ANI_STAND;
								setVx(0);
							}
						}
						else
						{
							if (isAttack) {
								state = SIMON_STATE_ATTACK_STAND;
								setVx(0);
								attackStandDelay.start();

							}
							else
							{

								aniIndex = SIMON_ANI_STAND;
								if(!isOnGiaDo)
									setVx(0);
							}
						}
						
					}
				}
			}
			if (isJumpDown) {
				aniIndex = SIMON_ANI_JUMB;
				setVy(SIMON_JUMP_Y);
			}
		}
		else
		{
			aniIndex = SIMON_ANI_JUMB;
			if (isUpDown) {
				if (isAttack) {
					
					if (ScoreBar::getInstance()->getHeartCount() <= 0 || ScoreBar::getInstance()->getTypeSubWeapon() == DEFAUL || !canMakeSub) {
						state = SIMON_STATE_ATTACK_JUMP;
						attacJumbDelay.start();
					}
					else
					{
						state = SIMON_STATE_USE_SUB;
						attackUseSub.start();
						makeSubWeapon(ScoreBar::getInstance()->getTypeSubWeapon());
					}
				}
			}
			else
			{
				if (isAttack) {
					state = SIMON_STATE_ATTACK_JUMP;
					attacJumbDelay.start();
				}
			}
			
		}
	}
	 break;
	case SIMON_STATE_ATTACK_STAND:
	{
		aniIndex = SIMON_ANI_STAND_USING_SUB;
		break;
	}
	case SIMON_STATE_ATTACK_JUMP:
	{
		aniIndex = SIMON_ANI_STAND_USING_SUB;
		break;
	}
	case SIMON_STATE_ON_STAIR:
	{
		switch (playerStairState)
		{
		case SIMON_STAIR_STATE_NORUN:
			
			if (!isUpDown && !isDownDown)
			{
				setPauseAnimation(true);
				frameIndex = 0;
				setDx(0);
				setDy(0);
				setX(playerStairDestx);
				setY(playerStairDesty);
			}
			
			if (isUpDown)
			{
				goStairUp();
				
			}
			else
			{
				if (isDownDown)
				{
					goStairDown();

				}
				else
				{
					if (isAttack) {
						attackInStairDelay.start();
						setPauseAnimation(false);
						if (aniIndex == SIMON_ANI_ASCEND_STAIRS)
						{
							playerStairState = SIMON_STAIR_STATE_ATTACK_ASCEN;
							aniIndex = SIMON_ANI_ASCEN_STAIRS_USING_SUB;
						}
						else
						{
							if (aniIndex == SIMON_ANI_DESCEN_STAIRS)
							{
								playerStairState = SIMON_STAIR_STATE_ATTACK_DESEN;
								aniIndex = SIMON_ANI_DESCEN_STAIRS_USING_SUB;
							}
						}

					}
				}
			}
			return;
		case SIMON_STAIR_STATE_GO_UP:
			x += getDirection();
			/* go up stair */
			setDy(1);
			y += 1;
			break;
		case SIMON_STAIR_STATE_GO_DOWN:
			x += getDirection();
			/* go down stair */
			setDy(-1);
			y -= 1;
			
			break;
		case SIMON_STAIR_STATE_ATTACK_DESEN:

			if (attackInStairDelay.isTerminated())
			{
				playerStairState = SIMON_STAIR_STATE_NORUN;
			}
			break;
		case SIMON_STAIR_STATE_ATTACK_ASCEN:
			if (attackInStairDelay.isTerminated())
			{
				playerStairState = SIMON_STAIR_STATE_NORUN;
			}
			break;
		default:
			break;
		}
		/* phương thức xử lý chung khi đi (kiểm tra đến đích chưa để dừng lại) */
		if (playerStairState == SIMON_STAIR_STATE_GO_UP || playerStairState == SIMON_STAIR_STATE_GO_DOWN)
		{
			if (getDirection() == DIRECTION_RIGHT)
			{
				/* đang đi về phía bên phải */
				if (getX() + getDx() > playerStairDestx)
				{
					/* tới vị trí */
					setStartStair();
					setX(playerStairDestx);
					setY(playerStairDesty);

					/* nếu là lần di chuyển cuối cùng */
					if (getIsLastRunStair())
					{
						if (playerStairState == SIMON_STAIR_STATE_GO_DOWN) {
						/*	setY(getY() +30);*/
							setX(getX() + 5);
						}
						else
						{
							setY(getY() + 10);
							setX(getX() + 5);
						}
						
						setStopStair();
					}
				}
			}
			else
			{
				/* đang đi về bên trái */
				if (getX() + getDx() < playerStairDestx)
				{
					/* tới vị trí */
					setStartStair();
					/* đang đi về phía bên trái */

					setX(playerStairDestx);
					setY(playerStairDesty);

					/* nếu là lần di chuyển cuối cùng */
					if (getIsLastRunStair())
					{
						if (playerStairState == SIMON_STAIR_STATE_GO_DOWN) {
							/*setY(getY() +30 );*/
							setX(getX() - 5);
						}
						else {
							setY(getY() + 5);
							setX(getX() - 5);
						}
						
						setStopStair();
					}
				}
			}
		}
		break;
	}
	case SIMON_STATE_DIE: {
		setVx(0);
		if (deadDelay.isTerminated())
		{
			ScoreBar::getInstance()->increasePlayerLife(-1);
			ScoreBar::getInstance()->restoreHealth();
		/*	retoreWidthHeight();
			setY(getY() + 45);*/
			CGame::GetInstance()->SwitchScene(CGame::GetInstance()->current_scene);
			ScoreBar::getInstance()->setTypeSubWeapon(TYPE_SUBWEAPON::DEFAUL);
			state = SIMON_STATE_NORMAL ;
			aniIndex = SIMON_ANI_STAND;
			setVx(0);
			setVy(0);
		}
		return;
	}
	case SIMON_STATE_HURT: {
		if ( !jumbHurtTimeDelay.isOnTime()) {
		
			if (isJumpDown) {
				aniIndex = SIMON_ANI_JUMB;
				setVy(SIMON_JUMP_Y);
			}
			if (isRightDown) {
				setDirection(DIRECTION_RIGHT);
				aniIndex = SIMON_ANI_GO;
				setX(getX() + 1);
			}
			else
			{
				if (isLeftDown) {
					aniIndex = SIMON_ANI_GO;
					setDirection(DIRECTION_LEFT);
					setX(getX() - 1);
				}
				else
				{
					///*if (isJumpDown) {
					//	aniIndex = SIMON_ANI_JUMB;
					//	setY(15);
					//}
					//else
					//{*/
					//	aniIndex = SIMON_ANI_STAND;
					//}
					if (isDownDown) {
						/*state = SIMON_STATE_DUCK;
						setHeight(25);
						duckDelay.start();*/
					}
					else
					{
						if (isUpDown) {
							if (isAttack) {
								state = SIMON_STATE_USE_SUB;
								attackUseSub.start();
								makeSubWeapon(ScoreBar::getInstance()->getTypeSubWeapon());

							}
							else {

								aniIndex = SIMON_ANI_STAND;
							}
						}
						else
						{
							if (isAttack) {
								state = SIMON_STATE_ATTACK_STAND;
								attackStandDelay.start();

							}
							else
							{

								aniIndex = SIMON_ANI_STAND;
								if (!isOnGiaDo)
									setVx(0);
							}
						}

					}
				}

			}
		}
		
		return;
	}
	case SIMON_STATE_DUCK: {
		aniIndex = SIMON_ANI_JUMB;
		if (isAttack) {
			state = SIMON_STATE_ATTACK_DUCK;
			attackDuckDelay.start();
			/*return;*/
		}
		if (duckDelay.isTerminated())
		{
			if (!isDownDown) {
				
				state = SIMON_STATE_NORMAL;
				retoreWidthHeight();
				setY(getY() + 16);
			}
			else {
				duckDelay.start();
			}
			
		}
		
		break;

	}
	case SIMON_STATE_ATTACK_DUCK: {
		aniIndex = SIMON_ANI_DUCK_USING_SUB;
		//if (attackDuckDelay.isTerminated())
		//{
		//	state = SIMON_STATE_DUCK;
		//	/*retoreWidthHeight();
		//	setY(getY() + 16);*/
		//}
		break;
	}
	case SIMON_STATE_USE_SUB:
	{
		isUseSub = true;
		aniIndex = SIMON_ANI_STAND_USING_SUB;
		break;
	}
	case SIMON_STATE_HIDE:
		break;
	default:
		break;
	}
}

void Simon::Render()
{
	if (!getRenderActive())
		return;
	if(isAlive)
		animation_set->at(aniIndex)->Render(x, y,frameIndex , direction, pauseAnimation);	
}

void Simon::makeSubWeapon(TYPE_SUBWEAPON type) {
	SubWeaponAttack* sub;
	Simon::getInstance()->canMakeSub = false;
	switch (type)
	{
	case SWORD:
		ScoreBar::getInstance()->increaseHeartCount(-1);
		sub = new SubDaggerAttack();
		CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(sub);
		sub->setX(getMidX());
		sub->setY(getMidY() + 10);
		sub->setAlive(true);
		sub->setPhysicsEnable(true);
		sub->timeDelay.start();
		break;
	case BOOMERANG:
		ScoreBar::getInstance()->increaseHeartCount(-1);
		sub = new SubBoomerangAttack();
		CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(sub);
		sub->setX(getMidX());
		sub->setY(getMidY() + 10);
		sub->setAlive(true);
		sub->setPhysicsEnable(true);
		sub->timeDelay.start();
		sub->timeCheckSimon.start();
		break;
	case AXE:
		ScoreBar::getInstance()->increaseHeartCount(-1);
		sub = new SubAxeAttack();
		CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(sub);
		sub->setX(getMidX());
		sub->setY(getMidY() + 10);
		sub->setAlive(true);
		sub->setPhysicsEnable(true);
		sub->timeDelay.start();
		break;
	case BLUEPOTION:
		ScoreBar::getInstance()->increaseHeartCount(-1);
		sub = new SubFireBombAttack();
		CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(sub);
		sub->setX(getMidX());
		sub->setY(getMidY() +5);
		sub->setAlive(true);
		sub->setPhysicsEnable(true);
		sub->timeDelay.start();
		break;
	case STOPWATCH:
	{
		int heartCount = ScoreBar::getInstance()->getHeartCount();
		if (heartCount - 5 >= 0) {
			ScoreBar::getInstance()->increaseHeartCount(-5);
			sub = new SubStopWatchAttack();
			CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(sub);
			sub->setAlive(true);
			sub->timeDelay.start();
			CGame::GetInstance()->GetCurrentScene()->setStopUpdate(true);
		}
		Simon::getInstance()->canMakeSub = true;
		state = SIMON_STATE_ATTACK_STAND;
		setVx(0);
		attackStandDelay.start();
	}
		break;
	default:
		return;
	}
}
void Simon::retoreWidthHeight()
{
	setWidth(fixWidth);
	setHeight(fixHeight);
}

Item *Simon::getSubweapon()
{
	return subWeapon;
}

void Simon::setSubWeapon(Item* item)
{
	this->subWeapon = item;
}

void Simon::setNumberArchery(int num)
{
	this->numberArchery = num;
}

void Simon::addNumberObjectBlack(int num)
{
	numberObjectBlack += num;
}

int Simon::getNumberObjectBlack()
{
	return numberObjectBlack;
}

void Simon::setNumberObjectBlack(int init)
{
	numberObjectBlack = init;
}


int Simon::getNumberArchery()
{
	return numberArchery;
}

void Simon::addNumberArchery(int num)
{
	this->numberArchery += num;
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);

}

int Simon::getState()
{
	return state;
}

void Simon::setAnChorRight()
{

}

void Simon::setAnChorLeft()
{
}

Simon* Simon::getInstance()
{
	if (instance == 0) {
		instance = new Simon();
	}
	return instance;
}

void Simon::setStartStair()
{

	/* tắt vật lý cho player */
	this->setPhysicsEnable(false);

	playerStairDestx = getX();
	playerStairDesty = getY();


	if (!isUpDown && !isDownDown)
	{
		/* tắt chuyển animation cho player */
		setPauseAnimation(true);
		this->setVx(0);
		this->setVy(0);
		this->setDx(0);
		this->setDy(0);
		frameIndex = 0;
	}

	/* set state lên cầu thang cho player */
	 state = SIMON_STATE_ON_STAIR;
	/* set player stair state */
	setPlayerStairState(SIMON_STAIR_STATE_NORUN);
	/* tắt xử lý va chạm */
	setStopCollision(true);
}

void Simon::setStopStair()
{
	/* nhưng chuyển động */
	this->setVx(0);
	this->setVy(0);
	this->setDx(0);
	this->setDy(0);
	setPauseAnimation(false);
	setStopCollision(false);
	setPhysicsEnable(true);
	state = SIMON_STATE_NORMAL;
	setIsLastRunStair(false);
}

bool Simon::getIsLastRunStair()
{
	return  isLastRunStair;
}

void Simon::setIsLastRunStair(bool isLastRunStair)
{
	this->isLastRunStair = isLastRunStair;
}

void Simon::goStairUp()
{
	playerStairDesty = getY() + 8;
	//stairDirection == 0 is right
	if (stairDirection == 0)
	{
		playerStairDestx += 5;
		setDirection(DIRECTION_LEFT);
	}
	else
	{
		playerStairDestx -= 5;
		setDirection(DIRECTION_RIGHT);
	}

	setPlayerStairState(SIMON_STAIR_STATE_GO_UP);
	/* cho player có lại animation khi lên cầu thang */
	setPauseAnimation(false);
	aniIndex = SIMON_ANI_ASCEND_STAIRS;
}

void Simon::goStairDown()
{
	playerStairDesty -= 8;
	if (stairDirection == 0)
	{
		playerStairDestx -= 5;
		setDirection(DIRECTION_RIGHT);
	}
	else
	{
		playerStairDestx += 5;
		setDirection(DIRECTION_LEFT);
	}

	setPlayerStairState(SIMON_STAIR_STATE_GO_DOWN);
	/* cho player có lại animation khi xuống cầu thang */
	setPauseAnimation(false);
	aniIndex = SIMON_ANI_DESCEN_STAIRS;
}

void Simon::setStairDirection(int stairDirection)
{
	this->stairDirection = stairDirection;
}

void Simon::setPlayerStairState(int playerStairState)
{
	this->playerStairState = playerStairState;
}

void Simon::setRenderActive(bool renderActive)
{
	this->renderActive = renderActive;
}

bool Simon::getRenderActive()
{
	return renderActive;
}

void Simon::onCollision(CGameObject* other, float collisionTime, int nx, int ny)
{
	
	CGameObject::onCollision( other,  collisionTime,  nx,  ny);
}

bool Simon::isDie() {
	if (ScoreBar::getInstance()->getHealth()-1 <= 0) {
		ScoreBar::getInstance()->increaseHealth(-1);
		aniIndex = SIMON_ANI_DEAD;
		state = SIMON_STATE_DIE;
		setHeight(animation_set->at(aniIndex)->getFrame(0)->GetSprite()->getHeight()-5);
		deadDelay.start();
		return true;
	}
	return false;
}
void Simon::setHurt( int directEnemy, float xOfEnemy) {
	if (!hurtTimeDelay.isOnTime())
	{
		state = SIMON_STATE_HURT;
		//setPhysicsEnable(false);
		//setStopCollision(true);

		/*setVx(-getDirection() * 0.003);
		setVy(0.04);*/


		/*hurtDelay.start();
		hideHurtDelay.start();
		if (hurtDelay.isOnTime()) {
			if (aniIndex != SIMON_ANI_HURT)
			{
				if (blinkTime.atTime()) {
					setRenderActive(false);
				}
			}
		}*/
		/*setVx(-getDirection() * 0.3);
		setVy(0.004);*/
		if (xOfEnemy < getX()) {
				setDirection(DIRECTION_LEFT);
				hurtDirection = 1;
		}
		else
		{
			setDirection(DIRECTION_RIGHT);
			hurtDirection = -1;
		}
		
		aniIndex = SIMON_ANI_HURT;
		//aniIndex = SIMON_ANI_HURT;
		hurtTimeDelay.start();
		jumbHurtTimeDelay.start();  
	}
}

void Simon::setHide()
{
	aniIndex = SIMON_ANI_HIDE;
	state = SIMON_STATE_HIDE;

}

void Simon::Load(LPCWSTR simonFile)
{
	DebugOut(L"[INFO] Start loading simon resources from : %s \n", simonFile);

	ifstream f;
	f.open(simonFile);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines
		if (line[0] == '/' && line[1] == '/') continue;	// skip comment lines

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;

		}
	}

}



