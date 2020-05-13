#include "Cell.h"

vector<int> Cell::getInxObjects()
{
	return inxObjList;
}

void Cell::setInxObjects(vector<int> inxList)
{
	this->inxObjList = inxList;
}

Cell::Cell()
{
}

Cell::~Cell()
{
}
