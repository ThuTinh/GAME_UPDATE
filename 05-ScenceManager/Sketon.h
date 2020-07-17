#pragma once
#include"Enemy.h"
#include "DelayTime.h"
#include "GameTime.h"
#define SKETON_SCORE 200
#define SKETON_VX 0.05
#define DISTANCE_TO_THROW_WHITEBONE 50
enum SKETON_STATE {
	SKETON_NOMAL,
	SKETON_JUMB 
};
class Sketon : public Enemy
{
	SKETON_STATE stateSKeton;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void onCollision(CGameObject* other, float collisionTime, int nx, int ny) override;
	SKETON_STATE getStateSketon();
	void setStateSketon(SKETON_STATE state);
	DelayTime whiteBoneDelay;
	GameTime timeThrow;
	DelayTime timeJumb;
	DelayTime delayJumb;
	virtual void Render();
	Sketon();
	~Sketon();

private:

};

 