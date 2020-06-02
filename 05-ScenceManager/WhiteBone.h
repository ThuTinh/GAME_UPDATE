#pragma once
#include"GameObject.h"
#include "DelayTime.h"
#define VX 0.4
#define VY 0.8
#define TIME_DELAY 500
#define WHITE_BONE_ANI 51
#define WHITE_BONE_GRAVITY -0.005
class WhiteBone : public CGameObject
{
public:
	WhiteBone();
	~WhiteBone();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void setDirectionFollowPlayer();
	DelayTime timeDelay;
private:

};

