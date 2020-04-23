#pragma once
#include"Sprites.h"

/*Cần camara để vẽ title map	 */
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



	/* tilesheet */
	LPDIRECT3DTEXTURE9 tilesheet;

	/* ma trận tile */
	int** matrix;
public:


	/* vẽ tilemap bằng camera */
	void render(Camera* camera);

	/* lấy chiều cao của world dùng để chuyển đổi tọa độ khi init */
	int getWorldHeight();

	/* tilesheetPath: đường dẫn tilesheet
	matrixPath : đường dẫn file ma trận
	*/
	void Init(int idSheet, string matrixPath);
	/* folderPath : đường dẫn thư mục chứa ma trận và tilesheet */
	//void Init(const char* folderPath);
	int getTileWidth();
	int getTileHeight();
	int getTileRows();
	int getTileColumns();

	Tilemap();
	~Tilemap();
};

