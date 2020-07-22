#pragma once
#include"Item.h"
#define BOOMERANG_VY -0.2 
class BoomeRang : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	BoomeRang();
	~BoomeRang();

private:

};

