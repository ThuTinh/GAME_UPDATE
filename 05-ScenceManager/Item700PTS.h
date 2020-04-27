#pragma once
#include"Item.h"
#define ITEM700PTS_SCORE 700
class Item700PTS : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	Item700PTS();
	~Item700PTS();

private:

};

