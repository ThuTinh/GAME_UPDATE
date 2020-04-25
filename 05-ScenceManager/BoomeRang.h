#pragma once
#include"Item.h"
class BoomeRang : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	BoomeRang();
	~BoomeRang();

private:

};

