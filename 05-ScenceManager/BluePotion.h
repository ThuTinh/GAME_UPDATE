#pragma once
#include"Item.h"
class BluePotion : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	BluePotion();
	~BluePotion();

private:

};

