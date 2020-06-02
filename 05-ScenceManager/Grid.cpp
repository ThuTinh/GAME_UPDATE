#include "Grid.h"
#include "Utils.h"
#include <fstream>
vector<Cell*>* Grid::GetCells()
{
	return CellList;
}

vector<int> Grid::getInxInCamera()
{
	return inxInCamara;
}

void Grid::checkCellColitionCamera(Camera* camera)
{
	inxInCamara.clear();
	for (int i = 0; i < CellList->size(); i++) {
		if (CheckCollisionCamara(camera, CellList->at(i))) {
			vector<int> temp = CellList->at(i)->getInxObjects();
			for (int j = 0; j < temp.size(); j++) {
				inxInCamara.push_back(temp[j]);
			}

		}
	}
}

void Grid::Init(string gridPath)
{
	
	ifstream fs(gridPath);
	int count;
	int mapHeight;
	fs >> count;
	ignoreLineIfstream(fs, 1);
	fs >> mapHeight;
	ignoreLineIfstream(fs, 1);
	int x, y, with, countObj;
	for (int i = 0; i < count; i++) {
		Cell* cell = new Cell();
		fs >> x >> y >> with >> with >> countObj;
		cell->setX(x);
		cell->setY(mapHeight - y);
		cell->setHeight(with);
		cell->setWidth(with);
		if (countObj > 0) {
			vector<int> inxObjList;
			for (int j = 0; j < countObj; j++) {
				int index;
				fs >> index;
				inxObjList.push_back(index);
			}
			cell->setInxObjects(inxObjList);
		}
		CellList->push_back(cell);
		ignoreLineIfstream(fs, 1);
	}
}

bool Grid::CheckCollisionCamara( Camera* camera, Cell* cell)
{
	return ((camera->getX() < cell->getX() + cell->getWidth() && camera->getX() + camera->getWidth() > cell->getX()) &&
		(camera->getY() - camera->getHeight() < cell->getY() && camera->getY() > cell->getY() - cell->getHeight()));
}

Grid::Grid()
{
	CellList = new vector<Cell*>();
}

Grid::~Grid()
{
}
