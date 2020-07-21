#pragma once
#include"Item.h"
class Archery : public Item
{
public:
	Archery();
	~Archery();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;

};


