#pragma once
#include"Item.h"
class HaiXanh : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	HaiXanh();
	~HaiXanh();

private:

};

