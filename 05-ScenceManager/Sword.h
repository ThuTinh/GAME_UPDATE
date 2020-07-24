#pragma once
#include"Item.h"
#define SWORD_VY - 0.2
class Sword : public Item
{
public:
	Sword();
	~Sword();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void onPlayerContact() override;
private:

};

