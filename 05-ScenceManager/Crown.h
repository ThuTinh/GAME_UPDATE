#pragma once
#include"Item.h"
#define SCORE  2000
class Crown : public Item
{
	bool checkOnlyOne;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void restorePosition() override;
	Crown();
	~Crown();

private:

};

