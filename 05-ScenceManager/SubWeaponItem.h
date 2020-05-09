#pragma once
#include"Item.h"
#define NUMBER_HEART 1
class SubWeaponItem : public Item
{
public:
	SubWeaponItem();
	~SubWeaponItem();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render();
	void onPlayerContact();
private:

};


