#pragma once
#include"Item.h"
#define HAIXANH_VY -0.05
class HaiXanh : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	HaiXanh();
	~HaiXanh();

private:

};

