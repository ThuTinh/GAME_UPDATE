#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Simon.h"
#include "Goomba.h"
#include "Koopas.h"
#include"Tilemap.h"
#include"Space.h"


class CPlayScene: public CScene
{
protected: 
	Simon *player;					// A play scene has to have player, right? 
	Tilemap *titlemap;
	vector<LPGAMEOBJECT> objects;
	unordered_map<int, Space*> spaces;
	Space* currentSpace;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_SPACE(string line);
public: 
	CPlayScene(int id, LPCWSTR filePath);
	void setCurentSpace(int index);
	Space* getCurentSpace();
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

