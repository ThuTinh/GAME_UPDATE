#pragma once
#include"GameObject.h"
#include "DelayTime.h"
#include "GameTime.h"
#define VX 0.045
#define VY 0.25
#define TIME_DELAY 1200
#define TIME_CHECK 180
#define WHITE_BONE_ANI 51
#define WHITE_BONE_GRAVITY -0.0005
class WhiteBone : public CGameObject
{
public:
	WhiteBone();
	~WhiteBone();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render();
	GameTime timeCheck;
	DelayTime timeDelay;
private:

};

