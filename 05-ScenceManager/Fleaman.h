#pragma once
#include"Enemy.h"
class Fleaman : public Enemy
{
public:
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Fleaman();
	~Fleaman();

private:

};

