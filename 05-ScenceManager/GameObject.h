#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include"CollitionType.h"
#include "Sprites.h"
#include "Animations.h"
#include"Rect.h"

#define MAX(a,b) a>b? a:b
#define MIN(a,b) a>b? b:a
using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box



class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	
	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:

	float x; 
	float y;

	float width;
	float height;
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt
	
	float vx;
	float vy;

	int nx;	 
	int frameIndex;
	int state;
	DWORD dt; 
	LPANIMATION_SET animation_set;
	/* cho phép trọng lực hay không */
	bool physicsEnable;
	/* vật có đứng trên mặt sàn hay không */

	bool isAlive;
	COLLISION_TYPE collitionType;
	DIRECTION direction;
	int aniIndex;
	bool isLastFrameAnimationDone;
	bool pauseAnimation;
	bool stopCollision;
	Rect initBox;

public: 
	bool isOnGround;
	vector<COLLISION_TYPE> collitionTypeToCheck;
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void setX(float x);
	void setY(float y);
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void setWidth( float with);
	void setHeight(float height);
	float getWidth();
	float getHeight();
	float getRight();
	float getBottom();
	float getLeft();
	float getX();
	float getY();
	float getMidX();
	float getMidY();
	void setDx(float dx);
	void setDy(float dy);
	float getDx();
	float getDy();
	void setVx(float vx);
	void setVy(float vy);
	float getVx();
	float getVy();
	bool getPhysicsEnable();
	virtual void setPhysicsEnable(bool physicsEnable);
	bool getIsOnGround();
	void setIsOnGround(bool isOnGround);
	void setCollitionType(COLLISION_TYPE collitionType);
	COLLISION_TYPE getCollitionType();
	void setAlive( bool alive);
	bool getAlive();
	DIRECTION getDirection();
	void setDirection(DIRECTION direction);
	bool getIsLastFrameAnimationDone();
	virtual void setIsLastFrameAnimationDone(bool isLastFrameAnimationDone);
	bool AABBCheck(CGameObject* S);
	int GetState() { return this->state; }
	virtual void restorePosition();
	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny, 
		float &rdx, 
		float &rdy);

	CGameObject();
	 CGameObject* GetSweptBroadPhaseBox();
	 float SweptAABB(CGameObject* M, CGameObject* S, float& normalX, float& normalY);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void SetState(int state) { this->state = state; }
	virtual void onCollision(CGameObject* other, float collisionTime, int nx, int ny);
	void preventMovementWhenCollision(float collisionTime, int nx, int ny);
	void setPauseAnimation(bool pause);
	bool getPauseAnimation();
	void setStopCollision( bool stopCollision);
	bool getStopCollision();
	virtual void makeDieEffect();
	virtual void makeHitEffect();
	~CGameObject();
};

