#include"GameObject.h"
#include "DelayTime.h"

#pragma once
#define ENEMY_GRAVITY -0.00003
#define ENEMY_SCORE 500
class Enemy :  public CGameObject
{
public:
	DelayTime collisionDelay;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void onCollision(CGameObject* other, float collisionTime, int nx, int ny);
	void setDirectionFollowPlayer();
	virtual void onPlayerContact();
	Enemy();
	~Enemy();

private:

};

