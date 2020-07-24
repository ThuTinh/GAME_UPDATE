#pragma once
#pragma once
#include"Item.h"
#define AXE_VY - 0.2
class Axe : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	Axe();
	~Axe();

private:

};

