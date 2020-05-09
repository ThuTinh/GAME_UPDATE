#pragma once
#include"Item.h"
class BluePotion : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	BluePotion();
	~BluePotion();

private:

};

