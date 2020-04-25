#pragma once
#include"Sprites.h"
#include"Camera.h"

class Tilemap
{
	/* chiều rộng tile */
	int tileWidth;
	/* chiều dài tile */
	int tileHeight;
	/* số lượng dòng trong matrix */
	int tileRows;
	/* số lượng cột trong matrix */
	int tileColumns;
	/* số lượng cột trong tilesheet */
	int tilesheetColumns;

	LPDIRECT3DTEXTURE9 tilesheet;

	/* ma trận tile */
	int** matrix;
public:


	/* vẽ tilemap bằng camera */
	void render(Camera* camera);
	int getWorldHeight();
	void Init(int idSheet, string matrixPath);
	int getTileWidth();
	int getTileHeight();
	int getTileRows();
	int getTileColumns();

	Tilemap();
	~Tilemap();
};

