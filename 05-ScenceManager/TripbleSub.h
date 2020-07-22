#pragma once
#include"Item.h"
#define TRIPBLE_VY - 0.2
class TripbleSub : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	TripbleSub();
	~TripbleSub();

private:

};

