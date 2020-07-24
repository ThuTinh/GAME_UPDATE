#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Simon.h"
#include"Tilemap.h"
#include"Space.h"
#include"Grid.h"
#include "KeyStart.h"

class IntroSence : public CScene
{
protected:
	Simon* player;	
	//KeyStart* keyStart;// A play scene has to have player, right? 
	Tilemap* titlemap;
	vector<LPGAMEOBJECT> objects;
	Space* currentSpace;
	vector<int> texturesID;
	vector<int> spritesID;
	vector<int> animationsID;
	vector<int> animationSetsID;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_SPACE(string line);

public:
	IntroSence(int id, LPCWSTR filePath);
	unordered_map<int, Space*> spaces;
	void setCurentSpace(int index);
	Space* getCurentSpace();
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void setStopUpdate(bool stop);
	virtual bool getStopUpdate();
	virtual void addAddtionalObject(LPGAMEOBJECT obj);
	virtual vector<LPGAMEOBJECT> getAddtionalObject();
	friend class IntroScenceKeyHandler;
};

class IntroScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	IntroScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

