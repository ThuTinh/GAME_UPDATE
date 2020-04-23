#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;
enum DIRECTION
{
	DIRECTION_LEFT = -1,
	DIRECTION_RIGHT = 1
};
class CSprite
{
	int id;				// Sprite ID in the sprite database

	int x; 
	int y;
	int width;
	int height;
	int anchorX;
	int anchorY;
	DIRECTION direction;
	LPDIRECT3DTEXTURE9 texture;
public: 
	CSprite(int id, int x, int y, int witdh, int height, int anchorX, int anchorY, LPDIRECT3DTEXTURE9 tex);
	float getleft();
	float getRight();
	float getTop();
	float getBottom();
	int getWidth();
	int getHeight();
	void setAnchorX(int anchorX);
	void setAnchorY(int anchorY);
	int getAnchorX();
	int getAnchorY();
	void Draw(float x, float y, DIRECTION direction,int alpha = 255);
	void setDirection(DIRECTION direction);
	DIRECTION getDirection();
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int x, int y, int with, int height, int anchorX, int anchorY, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	void CSprites::Clear();

	static CSprites * GetInstance();
};



