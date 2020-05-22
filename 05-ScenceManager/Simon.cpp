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
#include "SubDaggerAttack.h"
#include "SubBoomerangAttack.h"
#include "SubWeaponAttack.h"
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
	setCollitionType(COLLISION_TYPE_GROUND);
	setPhysicsEnable(true);
	setVx(0);
	setAlive(true);
	setDirection(DIRECTION_RIGHT);
	SetState(SIMON_STATE_NORMAL);
	setNumberArchery(0);
	isUseSub = false;
	attackStandDelay.init(400);
	attacJumbDelay.init(400);
	colorDelay.init(300);
	hurtDelay.init(200);
	deadDelay.init(200);
	duckDelay.init(200);
	attackUseSub.init(400);
	//jumbDelay.init(80);
	attackDuckDelay.init(400);
	setCollitionType(COLLISION_TYPE_PLAYER);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	collitionTypeToCheck.push_back(COLLISION_TYPE_ENEMY);



}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	
	attackStandDelay.update();
	colorDelay.update();
	hurtDelay.update();
	duckDelay.update();
	attacJumbDelay.update();
	attackDuckDelay.update();
	attackUseSub.update();
	
	if (aniIndex == SIMON_ANI_COLORS) {
		
		if(colorDelay.isTerminated()) {
			Simon::getInstance()->aniIndex = SIMON_ANI_STAND;
		}
		else
		{
			return;
		}
	}
	
	CGameObject::Update(dt);
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
				if (!dynamic_cast<Ground*>(e->obj)) {
					
					if (dynamic_cast<Enemy*>(e->obj)) {
						//e->obj->onCollision(e->obj, e->t, e->nx, e->ny); 
						aniIndex = SIMON_ANI_HURT;
						state = SIMON_STATE_HURT;
						hurtDelay.start();
						if (ScoreBar::getInstance()->getHealth() <= 0) {
							ScoreBar::getInstance()->increasePlayerLife(-1);
							aniIndex = SIMON_ANI_DEAD;
							state = SIMON_STATE_DIE;
							setHeight(animation_set->at(aniIndex)->getFrame(0)->GetSprite()->getHeight());
							deadDelay.start();
						}
					}
				}
				else
				{
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
					if (isDownDown) {
						state = SIMON_STATE_DUCK;
						setHeight(25);
						duckDelay.start();
					}
					else
					{
						if (isUpDown) {
							if (isAttack)    {
								state = SIMON_STATE_USE_SUB;	
								attackUseSub.start();
								SubWeaponAttack* sub;
								switch (ScoreBar::getInstance()->getTypeSubWeapon())
								{
								case SWORD:
									sub = new SubDaggerAttack();
									CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(sub);
									sub->setX(getMidX());
									sub->setY(getMidY() + 10);
									sub->setAlive(true);
									sub->setPhysicsEnable(true);
									sub->timeDelay.start();
									break;
								case BOOMERANG:
									sub = new SubBoomerangAttack();
									CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(sub);
									sub->setX(getMidX());
									sub->setY(getMidY() + 10);
									sub->setAlive(true);
									sub->setPhysicsEnable(true);
									sub->timeDelay.start();
									break;
								default:
									return;
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
								attackStandDelay.start();

							}
							else
							{

								aniIndex = SIMON_ANI_STAND;
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
			if (isAttack) {
				state = SIMON_STATE_ATTACK_JUMP;
				attacJumbDelay.start();
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
			if (isDownDown)
			{
				goStairDown();
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
						setY(getY() + 15);
						setX(getX() + 10);
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
						setY(getY() + 10);
						setX(getX() - 10);
						setStopStair();
					}
				}
			}
		}
		break;
	}
	case SIMON_STATE_DIE: {
		deadDelay.update();
		setVx(0);
		if (deadDelay.isTerminated())
		{
			ScoreBar::getInstance()->restoreHealth();
			ScoreBar::getInstance()->restoreBossHealth();
			retoreWidthHeight();
			setY(getY()+16);
			state = SIMON_STATE_NORMAL ;
		}
		return;
	}
	case SIMON_STATE_HURT: {
		
		if (hurtDelay.isTerminated()) {
			ScoreBar::getInstance()->increaseHealth(-1);
			state = SIMON_STATE_NORMAL;
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
	default:
		break;
	}
}

void Simon::Render()
{	
	animation_set->at(aniIndex)->Render(x, y,frameIndex , direction, pauseAnimation);	
}

void Simon::retoreWidthHeight()
{
	setWidth(fixWidth);
	setHeight(fixHeight);
}

Item *Simon::getSubweapo()
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

void Simon::onCollision(CGameObject* other, float collisionTime, int nx, int ny)
{
	CGameObject::onCollision( other,  collisionTime,  nx,  ny);
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



