#pragma once
#include "Cell.h"
#include "Camera.h"


class Grid
{
public:
	vector<Cell*>* GetCells();
	vector<int> getInxInCamera();
	void checkCellColitionCamera(Camera* camera);
	void Init(string gridPath);
	bool CheckCollisionCamara(Camera* camera, Cell* cell);

	Grid();
	~Grid();

private:
	vector<Cell*>* CellList;
	vector <int> inxInCamara;


};

