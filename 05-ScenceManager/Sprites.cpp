#include "Sprites.h"
#include "Game.h"
#include "Utils.h"

CSprite::CSprite(int id, int x, int y, int width, int height, int anchorX, int anchorY, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->anchorX = anchorX;
	this->anchorY = anchorY;
	this->texture = tex;
	this->direction = DIRECTION_LEFT;

}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, DIRECTION direction,int alpha)
{
	CGame * game = CGame::GetInstance();


	DIRECTION imageDirection = this->direction;

	/* hướng mặt của nhân vật */
	DIRECTION currentDirection = direction;


	/* nếu hướng mặt của nhân vật khác với hướng mặt trong bức hình thì tiến hành lật hình */
	if (imageDirection != currentDirection)
	{
		int currentFrameWidth = getRight() - getleft();
		D3DXMATRIX flipMatrix;
		D3DXMatrixIdentity(&flipMatrix);
		flipMatrix._11 = -1;
		flipMatrix._41 = 2 * (x + currentFrameWidth / 2) - currentFrameWidth + getWidth();
		game->GetSpriteHandler()->SetTransform(&flipMatrix);
	}

	/* vẽ đối tượng lên màn hình */
	game->Draw(x, y, getAnchorX(), getAnchorY(), texture, getleft(), getTop(), getRight(), getBottom(), alpha);

	if (direction != imageDirection)
	{
		/* khôi phục lại ma trận mặc định */
		D3DXMATRIX identityMatrix;
		D3DXMatrixIdentity(&identityMatrix);
		game->GetSpriteHandler()->SetTransform(&identityMatrix);
	}


}

void CSprite::setDirection(DIRECTION direction)
{
	this->direction = direction;
}

DIRECTION CSprite::getDirection()
{
	return direction;
}

void CSprites::Add(int id, int x, int y, int width, int height,int anchorX, int anchorY, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, x, y, width, height, anchorX, anchorY, tex);
	sprites[id] = s;

	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d \n", id, x, y, width, height);
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

/*
	Clear all loaded textures
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}



float CSprite::getleft()
{
	return x;
}

float CSprite::getRight()
{
	return x + width;
}

float CSprite::getTop()
{
	return y;
}

float CSprite::getBottom()
{
	return y + height;
}

int CSprite::getWidth()
{
	return width;
}

int CSprite::getHeight()
{
	return height;
}

void CSprite::setAnchorX(int anchorX)
{
	this->anchorX = anchorX;
}

void CSprite::setAnchorY(int anchorY)
{
	this->anchorY = anchorY;
}

int CSprite::getAnchorX()
{
	return anchorX;
}

int CSprite::getAnchorY()
{
	return anchorY;
}
