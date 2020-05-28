#pragma once
#include"Enemy.h"
#define SKETON_SCORE 200
#define SKETON_VX 0.03
class Sketon : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void onCollision(CGameObject* other, float collisionTime, int nx, int ny) override;

	virtual void Render();
	Sketon();
	~Sketon();

private:

};

