#pragma once
#include"Item.h"
#define STOPWATCH_VY - 0.2
class StopWatch : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	StopWatch();
	~StopWatch();

private:

};

