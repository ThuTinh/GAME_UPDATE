#pragma once
#include"Item.h"
#define ID_ANI_HEART 3
class BigHeart : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	BigHeart();
	~BigHeart();

private:

};

