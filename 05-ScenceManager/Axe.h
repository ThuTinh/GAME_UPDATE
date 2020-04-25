#pragma once
#pragma once
#include"Item.h"
class Axe : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	Axe();
	~Axe();

private:

};

