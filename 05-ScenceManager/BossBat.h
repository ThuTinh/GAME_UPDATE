#pragma once
#include"Enemy.h"

class BossBat : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	BossBat();
	~BossBat();

private:

};

