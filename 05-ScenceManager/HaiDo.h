#pragma once
#include"Item.h"
class HaiDo : public Item
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	HaiDo();
	~HaiDo();

private:

};

