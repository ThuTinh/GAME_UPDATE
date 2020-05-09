#pragma once
#include"Item.h"
class HaiDo : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	HaiDo();
	~HaiDo();

private:

};

