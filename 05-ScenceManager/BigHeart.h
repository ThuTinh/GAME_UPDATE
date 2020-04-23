#pragma once
#include"Item.h"
class BigHeart : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	BigHeart();
	~BigHeart();

private:

};

