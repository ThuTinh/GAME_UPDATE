#pragma once
#include"Item.h"
class Crown : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	Crown();
	~Crown();

private:

};

