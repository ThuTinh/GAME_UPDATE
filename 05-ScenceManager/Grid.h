#pragma once
#include "Cell.h"
#include "Camera.h"

class Grid
{
public:
	vector<Cell*>* GetCells();
	vector<int> getInxInCamera();
	void checkCellColitionCamera(Camera* camera);
	void init(string gridPath);
	bool checkCollisionCamara(Camera* camera, Cell* cell);

	Grid();
	~Grid();

private:
	vector<Cell*>* CellList;
	vector <int> inxInCamara;


};

