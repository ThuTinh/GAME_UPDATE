#pragma once
#include"Item.h"
class TripbleSub : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	TripbleSub();
	~TripbleSub();

private:

};

