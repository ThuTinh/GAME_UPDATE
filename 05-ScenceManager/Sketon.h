#pragma once
#include"Enemy.h"
#include "DelayTime.h"
#include "GameTime.h"
#define SKETON_SCORE 200
#define SKETON_VX 0.05
#define DISTANCE_TO_THROW_WHITEBONE 50
class Sketon : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void onCollision(CGameObject* other, float collisionTime, int nx, int ny) override;
	DelayTime whiteBoneDelay;
	GameTime timeThrow;
	virtual void Render();
	Sketon();
	~Sketon();

private:

};

 