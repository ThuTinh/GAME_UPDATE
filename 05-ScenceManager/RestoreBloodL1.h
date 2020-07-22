#pragma once
#include"Item.h"
#define ID_ANI_HEART 3
#define RESTORE_BLOODL1 -0.2
class RestoreBloodL1 : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	RestoreBloodL1();
	~RestoreBloodL1();

private:

};

