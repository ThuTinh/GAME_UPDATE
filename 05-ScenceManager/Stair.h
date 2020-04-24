#pragma once
#include"GameObject.h"
class Stair : public CGameObject
{
	bool isRightStair, isTop;

public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void setRightTop(bool isRightStair, bool isTop);
	Stair();
	~Stair();

private:

};

