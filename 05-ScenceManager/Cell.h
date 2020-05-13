#pragma once
#include "Rect.h"
#include"Sprites.h"

class Cell : public Rect
{
public:

	vector<int> getInxObjects();
	void setInxObjects(vector<int> inxList);

	Cell();
	~Cell();

private:

	vector<int> inxObjList;

};

