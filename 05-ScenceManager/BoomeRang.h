#pragma once
#include"Item.h"
class BoomeRang : public Item
{
public:
	BoomeRang();
	~BoomeRang();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;


private:

};


