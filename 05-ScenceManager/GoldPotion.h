#pragma once
#include"Item.h"
class GoldPotion : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	GoldPotion();
	~GoldPotion();

private:

};

