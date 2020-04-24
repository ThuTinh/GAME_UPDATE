#include"GameObject.h"
#pragma once
#define ENEMY_GRAVITY -0.00002
class Enemy :  public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void setDirectionFollowPlayer();
	Enemy();
	~Enemy();

private:

};

