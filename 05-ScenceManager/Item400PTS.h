#pragma once
#include"Item.h"
#define ITEM400PTS_SCORE 400
class Item400PTS : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	Item400PTS();
	~Item400PTS();

private:

};

