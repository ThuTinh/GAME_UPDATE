#pragma once
#include"Item.h"
class Item400PTS : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	Item400PTS();
	~Item400PTS();

private:

};

