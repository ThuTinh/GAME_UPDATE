#pragma once
#include"Item.h"
class BigHeart : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	BigHeart();
	~BigHeart();

private:

};

