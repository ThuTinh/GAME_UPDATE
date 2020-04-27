#pragma once
#include"Item.h"
class HaiXanh : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void onPlayerContact() override;
	HaiXanh();
	~HaiXanh();

private:

};

