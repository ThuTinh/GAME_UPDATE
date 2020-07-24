#pragma once
#include"Item.h"
#define RESTORE_BLOOD -0.2
class RestoreBlood : public Item
{
public:
	RestoreBlood();
	~RestoreBlood();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render();
	void onPlayerContact();
private:

};


