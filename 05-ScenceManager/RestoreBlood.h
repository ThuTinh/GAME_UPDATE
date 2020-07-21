#pragma once
#include"Item.h"
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


