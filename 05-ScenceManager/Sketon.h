#pragma once
#include"Enemy.h"
#define SKETON_SCORE 200
class Sketon : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Sketon();
	~Sketon();

private:

};

