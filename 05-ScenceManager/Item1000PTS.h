#pragma once
#include"Item.h"
class Item1000PTS : public Item
{
public:
	Item1000PTS();
	~Item1000PTS();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	void Render();

private:

};


