#pragma once
#include"Enemy.h"
#define ZOOMBIE_SCORE 100
class Zoombie : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Zoombie();
	~Zoombie();

private:

};

