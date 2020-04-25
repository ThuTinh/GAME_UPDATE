#include "Tilemap.h"
#include"Game.h"
#include<fstream>
#include<string>
#include"Utils.h"
#include"Textures.h"
using namespace std;



void Tilemap::render(Camera* camera)
{
	/* height của world */
	int mapHeight = tileRows * tileHeight;

	/* tính các tile đang cắt camera */
	int tileLeft, tileRight, tileTop, tileBottom;

	/* tileLeft là vị trí cột camera cắt bên trái */
	tileLeft = camera->getleft() / tileWidth;

	/* tileRight là vị trí cột camera cắt bên phải */
	tileRight = camera->getRight() / tileWidth;

	/* tileTop là vị trí dòng camera cắt bên trên */
	tileTop = (mapHeight - camera->getTop()) / tileHeight;
	/* tileBottom là vị trí dòng camera cắt bên dưới */
	tileBottom = (mapHeight - camera->getBottom()) / tileHeight;

	/* điều kiện ràng buộc chống lỗi vượt quá index */
	if (tileLeft < 0)
	{
		tileLeft = 0;
	}

	if (tileTop < 0)
	{
		tileTop = 0;
	}

	if (tileRight >= tileColumns)
	{
		tileRight = tileColumns - 1;
	}

	if (tileBottom >= tileRows)
	{
		tileBottom = tileRows - 1;
	}
	/* duyệt các tile cắt camera và vẽ chúng lên màn hình */
	for (size_t rowIndex = tileTop; rowIndex <= tileBottom; rowIndex++)
	{
		for (size_t columnIndex = tileLeft; columnIndex <= tileRight; columnIndex++)
		{
			/* tính vị trí world của tile */
			int xWorldOfTile = columnIndex * tileWidth;
			int yWorldOfTile = mapHeight - rowIndex * tileHeight;

			/* tính vị trí view của tile */

			float xViewOfTile = 0;
			float yViewOfTile = 0;

			camera->convertWorldToView(xWorldOfTile, yWorldOfTile, xViewOfTile, yViewOfTile);

			/* tìm hình chữ nhật là vị trí của tile trong tilesheet */
			int tileValue = matrix[rowIndex][columnIndex];

			int xTileInTileSheet = tileWidth * (tileValue % tilesheetColumns);
			int yTileInTileSheet = tileHeight * (tileValue / tilesheetColumns);
			int widthTileInTilesheet = tileWidth;
			int heightTileInTilesheet = tileHeight;

			RECT rectCrop;
			SetRect(&rectCrop,
				xTileInTileSheet, /* left */
				yTileInTileSheet, /* top */
				xTileInTileSheet + widthTileInTilesheet, /* right */
				yTileInTileSheet + heightTileInTilesheet); /* bottom */

			/* vẽ tile lên màn hình tại vị trí view */
			//tilesheet->Draw(xViewOfTile, yViewOfTile, 0, 0, &rectCrop);
			CGame::GetInstance()->DrawRect(xViewOfTile, yViewOfTile, 0, 0, tilesheet, rectCrop);
		}
	}
}

int Tilemap::getWorldHeight()
{
	return tileRows * tileHeight;
}

void Tilemap::Init(int idSheet, string matrixPath)
{
	tilesheet = CTextures::GetInstance()->Get(idSheet);
	auto tempPath = ToWSTR(matrixPath);

	auto Path = tempPath.c_str();
	/* khởi tạo matrix */
	fstream fs(Path);
	fs >> tileRows >> tileColumns >> tileWidth >> tileHeight >> tilesheetColumns;

	int k = 5;
	/* khởi tạo ma trận */
	matrix = new int* [tileRows];

	for (size_t rowIndex = 0; rowIndex < tileRows; rowIndex++)
	{
		matrix[rowIndex] = new int[tileColumns];
		for (size_t columnIndex = 0; columnIndex < tileColumns; columnIndex++)
		{
			/* đọc thông số ma trận tile file */
			fs >> matrix[rowIndex][columnIndex];
		}
	}

}

int Tilemap::getTileWidth()
{
	return  tileWidth;
}
int Tilemap::getTileHeight()
{
	return tileHeight;
}
int Tilemap::getTileRows()
{
	return tileRows;
}
int Tilemap::getTileColumns()
{
	return tileColumns;
}
Tilemap::Tilemap()
{
}
Tilemap::~Tilemap()
{
}
