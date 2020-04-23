#include <d3dx9.h>
#include <algorithm>
#include"Gound.h"
#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	setAlive(true);
}

void CGameObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top =  y - height/2;
	right = x + width;
	bottom = y + height;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	setIsOnGround(false);
	if (getPhysicsEnable())
	{
		this->dt = dt;
		dx = vx * dt;
		dy = vy * dt;
	}

}

void CGameObject::onCollision(CGameObject* other, float collisionTime, int nx, int ny)
{
	
	if (ny == 1 && dynamic_cast<Ground*>(other))
	{
		preventMovementWhenCollision(collisionTime,nx, ny);
		/* isOnGround = true tức vật có đứng trên sàn */
		setIsOnGround(true);
		vy = 0;

	}
	
}

void CGameObject::preventMovementWhenCollision(float collisionTime, int nx, int ny)
{
	/* dời vật M về sát vật S */
	if (nx != 0)
	{
		/* nếu vật va chạm theo phương x */
		setDx(collisionTime * getDx());
	}
	if (ny != 0)
	{
		/* nếu vật va chạm theo phương y */
		setDy(collisionTime * getDy());
	}
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny, float &rdx, float &rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_ix>=0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy>=0) coEventsResult.push_back(coEvents[min_iy]);
}

bool CGameObject::AABBCheck(CGameObject* S)
{
	return ((getX() < S->getX() + S->getWidth() && getX() + getWidth() > S->getX()) &&
		(getY() -getHeight() < S->getY() && getY() > S->getY() - S->getHeight()));
}
void CGameObject::setX(float x)
{
	this->x = x;
}

void CGameObject::setY(float y)
{
	this->y = y;
}

void CGameObject::setWidth(float with)
{
	this->width = with;

}

void CGameObject::setHeight(float height)
{
	this->height = height;
}

float CGameObject::getWidth()
{
	return width;
}

float CGameObject::getHeight()
{
	return height;
}

float CGameObject::getRight()
{
	return  x + width;
}

float CGameObject::getX()
{
	return x;
}

float CGameObject::getY()
{
	return y;
}



void CGameObject::setDx(float dx)
{
	this->dx = dx;
}

void CGameObject::setDy(float dy)
{
	this->dy = dy;
}

float CGameObject::getDx()
{
	return dx;
}

float CGameObject::getDy()
{
	return dy;
}

void CGameObject::setVx(float vx)
{
	this->vx = vx;
}

void CGameObject::setVy(float vy)
{
	this->vy = vy;
}

float CGameObject::getVx()
{
	return vx;
}

float CGameObject::getVy()
{
	return vy;
}



bool CGameObject::getPhysicsEnable()
{
	return physicsEnable;
}

void CGameObject::setPhysicsEnable(bool physicsEnable)
{
	this->physicsEnable = physicsEnable;
}

bool CGameObject::getIsOnGround()
{
	return isOnGround;
}

void CGameObject::setIsOnGround(bool isOnGround)
{
	this->isOnGround = isOnGround;
}

void CGameObject::setCollitionType(COLLISION_TYPE collitionType)
{
	this->collitionType = collitionType;
}

COLLISION_TYPE CGameObject::getCollitionType()
{
	return collitionType;
}

void CGameObject::setAlive(bool alive)
{
	this->isAlive = alive;
}

bool CGameObject::getAlive()
{
	return isAlive;
}

DIRECTION CGameObject::getDirection()
{
	return direction;
}

void CGameObject::setDirection(DIRECTION direction)
{
	this->direction = direction;
}

bool CGameObject::getIsLastFrameAnimationDone()
{
	return isLastFrameAnimationDone;
}

void CGameObject::setIsLastFrameAnimationDone(bool isLastFrameAnimationDone)
{
	this->isLastFrameAnimationDone = isLastFrameAnimationDone;
}

float CGameObject::getMidX()
{
	return x + width / 2;
}

float CGameObject::getMidY()
{
	return y - height / 2;
}

CGameObject::~CGameObject()
{

}