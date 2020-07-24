#pragma once
#include"Item.h"
#define ARCHERY_VY - 0.2
class Archery : public Item
{
public:
	Archery();
	~Archery();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;

};


