#pragma once
#include"Item.h"
#define NUMBER_HEART 1
#define HEART_SMALL_VX 0.0002
#define HEART_SMALL_VY -0.09

class RestoreBlood : public Item
{
public:
	RestoreBlood();
	~RestoreBlood();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render();
	void onPlayerContact();
private:

};


