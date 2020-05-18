#pragma once
#include"Item.h"
#define SCORE  2000
class Crown : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	Crown();
	~Crown();

private:

};

