#pragma once
#include"Enemy.h"
class Sketon : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Sketon();
	~Sketon();

private:

};

