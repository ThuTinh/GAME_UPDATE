//#include "Grid.h"
//#include<string>
//#include"Utils.h"
//std::vector<Cell*>* Grid::GetCells()
//{
//	return nullptr;
//}
//
//std::vector<int> Grid::getInxInCamera()
//{
//	return std::vector<int>();
//}
//
//void Grid::checkCellColitionCamera(Camera* camera)
//{
//}
//
//void Grid::Init(std::string gridPath)
//{
//	ifstream fs(gridPath);
//
//	int count;
//	int mapHeight;
//	fs >> count;
//	ignoreLineIfstream(fs, 1);
//	fs >> mapHeight;
//	ignoreLineIfstream(fs, 1);
//	int x, y, with, countObj;
//	for (int i = 0; i < count; i++) {
//		Cell* cell = new Cell();
//		fs >> x >> y >> with >> with >> countObj;
//		cell->setX(x);
//		cell->setY(mapHeight - y);
//		cell->setHeight(with);
//		cell->setWidth(with);
//		if (countObj > 0) {
//			std::vector<int> inxObjList;
//			for (int j = 0; j < countObj; j++) {
//				int index;
//				fs >> index;
//				inxObjList.push_back(index);
//
//			}
//			cell->setInxObjects(inxObjList);
//		}
//		CellList->push_back(cell);
//		ignoreLineIfstream(fs, 1);
//
//	}
//}
//
//
//Grid::Grid()
//{
//}
//
//Grid::~Grid()
//{
//}
