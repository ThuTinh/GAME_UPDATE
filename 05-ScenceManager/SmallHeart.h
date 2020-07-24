#pragma once
#include"Item.h"
#define NUMBER_HEART 1
#define SMALLHEART_VY - 0.05
class SmallHeart : public Item
{
public:
	SmallHeart();
	~SmallHeart();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render();
	void onPlayerContact();
private:

};


