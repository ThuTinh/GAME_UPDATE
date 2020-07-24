#pragma once
#include"Item.h"
#define GOLD_VY -0.2 
class GoldPotion : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	GoldPotion();
	~GoldPotion();

private:

};

