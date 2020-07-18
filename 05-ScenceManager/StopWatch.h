#pragma once
#include"Item.h"
class StopWatch : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	StopWatch();
	~StopWatch();

private:

};

