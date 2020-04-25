#pragma once
#include"Item.h"
class SmallHeart : public Item
{
public:
	SmallHeart();
	~SmallHeart();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	

private:

};


