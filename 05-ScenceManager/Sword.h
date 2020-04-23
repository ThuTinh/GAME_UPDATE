#pragma once
#include"Item.h"
class Sword : public Item
{
public:
	Sword();
	~Sword();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
private:

};

