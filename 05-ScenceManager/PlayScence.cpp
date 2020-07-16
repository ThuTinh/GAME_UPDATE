#include <iostream>
#include <fstream>
#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include"Gound.h"
#include"Camera.h"
#include"Fire.h"
#include"BigHeart.h"
#include"Archery.h"
#include"Sword.h"
#include"Weapon.h"
#include"Item1000PTS.h"
#include"Light.h"
#include"BlackNight.h"
#include"Stair.h"
#include"Gate.h"
#include"GateStair.h"
#include"GateStairChangeDirection.h"
#include"ScoreBar.h"
#include"SmallHeart.h"
#include"Sword.h"
#include"Axe.h"
#include"Item700PTS.h"
#include"Item400PTS.h"
#include"StopWatch.h"
#include"HaiXanh.h"
#include"GoldPotion.h"
#include"BluePotion.h"
#include"BoomeRang.h"
#include"Bat.h"
#include"Fleaman.h"
#include"Raven.h"
#include"Sketon.h"
#include"Zoombie.h"
#include"GiaDo.h"
#include "Ghost.h"
#include"Crown.h"
#include "BossBat.h"
#include"ObjectBlack.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	titlemap = new Tilemap();
}

void CPlayScene::setCurentSpace(int spaceID)
{
	this->currentSpace = spaces[spaceID];
	Camera::getInstance()->setSpace(this->currentSpace);
	Camera::getInstance()->setLocation(getCurentSpace()->CameraX, getCurentSpace()->CameraY);
	player->SetPosition(getCurentSpace()->PlayerX, getCurentSpace()->PlayerY);
}

Space* CPlayScene::getCurentSpace()
{
	return currentSpace;
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_MAP	3
#define SCENE_SECTION_SPRITES 4
#define SCENE_SECTION_ANIMATIONS 5
#define SCENE_SECTION_ANIMATION_SETS 6
#define SCENE_SECTION_OBJECTS	7
#define SCENE_SECTION_SPACE	8
#define SCENE_SECTION_STAIR 9
#define SCENE_SECTION_GRID 10

#define OBJECT_TYPE_GATE3 -9
#define OBJECT_TYPE_GATE_STAIR_CHANGE_DIRECTION -8
#define OBJECT_TYPE_GATE_STAIR2 -7
#define OBJECT_TYPE_GATE2 -6
//#define OBJECT_TYPE_GATE_STAIR1_2 -5
#define OBJECT_TYPE_GATE_STAIR1 -4
#define OBJECT_TYPE_GATE1 -3
#define OBJECT_TYPE_GROUND	-1
#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_FIRE	1
#define OBJECT_TYPE_LIGHT	2
#define OBJECT_TYPE_LEAOPART	3
#define OBJECT_TYPE_ZOOMIE	4
#define OBJECT_TYPE_HEART_BIG	5
#define OBJECT_TYPE_ARCHERY	6
#define OBJECT_TYPE_SWORD	7
#define OBJECT_TYPE_WEAPON	8
#define OBJECT_TYPE_BLACK_NIGHT  9
#define OBJECT_TYPE_BAT  10
#define OBJECT_TYPE_SKETON  11
#define OBJECT_TYPE_FLEAMAN  12
#define OBJECT_TYPE_RAVEN  13
#define OBJECT_TYPE_HEART_SMALL  15
#define OBJECT_TYPE_1000PTS	16
#define OBJECT_TYPE_GOLDPOTION	17
#define OBJECT_TYPE_AXE	18
#define OBJECT_TYPE_HAIXANH	19
#define OBJECT_TYPE_BOOMERANG 20
#define OBJECT_TYPE_CROWN	21
#define OBJECT_TYPE_700PTS	22
#define OBJECT_TYPE_HAIDO	23
#define OBJECT_TYPE_BLUEPOTION	24
#define OBJECT_TYPE_400PTS	25
#define OBJECT_TYPE_DIE_EFECT	26
#define OBJECT_TYPE_BOSSBAT	27
#define OBJECT_TYPE_OBJECTBLACK 	28
#define OBJECT_TYPE_GIADO 30
#define OBJECT_TYPE_GHOST 32



#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());
	texturesID.push_back(texID);
	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 10) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int x = atoi(tokens[1].c_str());
	int y = atoi(tokens[2].c_str());
	int with = atoi(tokens[3].c_str());
	int height = atoi(tokens[4].c_str());
	int anchorX = atoi(tokens[5].c_str());
	int anchorY = atoi(tokens[6].c_str());
	int anchorXRight = atoi(tokens[7].c_str());
	int anchorYRight = atoi(tokens[8].c_str());
	int texID = atoi(tokens[9].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}
	spritesID.push_back(ID);
	CSprites::GetInstance()->Add(ID, x, y, with, height, anchorX, anchorY,anchorXRight, anchorYRight , tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}
	animationsID.push_back(ani_id);
	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}
	animationSetsID.push_back(ani_set_id);
	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	float width = atoi(tokens[3].c_str());
	float height = atoi(tokens[4].c_str());

	int ani_set_id = atoi(tokens[5].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON: {
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before! ");
			return;
		}
		player = Simon::getInstance();
		y = titlemap->getWorldHeight() - y;
		player->SetPosition(x, y);
		player->setWidth(width);
		player->setHeight(height);
		player->fixHeight = height;
		player->fixWidth = width;
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		player->SetAnimationSet(ani_set);
		return;
	}
		
	case OBJECT_TYPE_GROUND: obj = new Ground(); break;
	case OBJECT_TYPE_FIRE: obj = new Fire(); break;
	case OBJECT_TYPE_ARCHERY: obj = new Archery(); break;
	case OBJECT_TYPE_SWORD: obj = new Sword(); break;
	case OBJECT_TYPE_HEART_BIG: obj = new BigHeart(); break;
	case OBJECT_TYPE_WEAPON: { Weapon::instance = 0; obj = Weapon::getInstance(); break; }
	case OBJECT_TYPE_1000PTS: obj = new Item1000PTS(); break;
	case OBJECT_TYPE_LIGHT: obj = new Light(); break;
	case OBJECT_TYPE_BLACK_NIGHT: obj = new BlackNight(); break;
	case OBJECT_TYPE_GATE1: obj = new Gate(); break;
	case OBJECT_TYPE_GATE2: obj = new Gate(); break;
	case OBJECT_TYPE_GATE3: obj = new Gate(); break;
	case OBJECT_TYPE_GATE_STAIR1: obj = new GateStair(); break;
	case OBJECT_TYPE_GATE_STAIR2: obj = new GateStair(); break;
	case OBJECT_TYPE_GATE_STAIR_CHANGE_DIRECTION: obj = new GateStairChangeDirection(); break;
	case OBJECT_TYPE_HEART_SMALL: obj = new SmallHeart(); break;
	case OBJECT_TYPE_700PTS: obj = new Item700PTS(); break;
	case OBJECT_TYPE_400PTS: obj = new Item400PTS(); break;
	case OBJECT_TYPE_AXE: obj = new Axe(); break;
	case OBJECT_TYPE_BAT: obj = new Bat(); break;
	case OBJECT_TYPE_BOOMERANG: obj = new BoomeRang(); break;
	case OBJECT_TYPE_FLEAMAN: obj = new Fleaman(); break;
	case OBJECT_TYPE_SKETON: obj = new Sketon(); break;
	case OBJECT_TYPE_GOLDPOTION: obj = new GoldPotion(); break;
	case OBJECT_TYPE_BLUEPOTION: obj = new BluePotion(); break;
	case OBJECT_TYPE_GIADO: obj = new GiaDo(); break;
	case OBJECT_TYPE_ZOOMIE: obj = new Zoombie(); break;
	case OBJECT_TYPE_CROWN: obj = new Crown(); break;
	case OBJECT_TYPE_HAIXANH: obj = new HaiXanh(); break;
	case OBJECT_TYPE_HAIDO: obj = new StopWatch(); break;
	case OBJECT_TYPE_RAVEN : obj = new Raven(); break;
	case OBJECT_TYPE_GHOST: obj = new Ghost(); break;
	case OBJECT_TYPE_BOSSBAT: obj = new BossBat(); break;
	case OBJECT_TYPE_OBJECTBLACK: obj = new ObjectBlack(); break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	y = titlemap->getWorldHeight() - y;
	obj->SetPosition(x, y);
	obj->setWidth(width);
	obj->setHeight(height);
	if (ani_set_id != -1) {
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	}
		
	objects.push_back(obj);
}

void CPlayScene::_ParseSection_MAP(string line) {
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;
	titlemap->Init(atoi(tokens[0].c_str()), tokens[1]);

}
void CPlayScene::_ParseSection_SPACE(string line)
{
	Space* tempSpace = new Space();
	vector<string> tokens = split(line);
	if (tokens.size() < 9) return;
	int id = atoi(tokens[0].c_str());
	tempSpace->X = atoi(tokens[1].c_str());
	tempSpace->Y= atoi(tokens[2].c_str());
	tempSpace->Width = atoi(tokens[3].c_str());
	tempSpace->Height = atoi(tokens[4].c_str());
	tempSpace->CameraX = atoi(tokens[5].c_str());
	tempSpace->CameraY = atoi(tokens[6].c_str());
	tempSpace->PlayerX = atoi(tokens[7].c_str());
	tempSpace->PlayerY = atoi(tokens[8].c_str());
	tempSpace->CameraY = titlemap->getWorldHeight() - tempSpace->CameraY;
	tempSpace->PlayerY = titlemap->getWorldHeight() - tempSpace->PlayerY;
	tempSpace->Y = titlemap->getWorldHeight() - tempSpace->Y;
	spaces[id] = tempSpace;
	

}
void CPlayScene::_ParseSection_STAIR(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 8) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	float width = atoi(tokens[3].c_str());
	float height = atoi(tokens[4].c_str());
	int ani_set_id = atoi(tokens[5].c_str());
	bool isRight = atoi(tokens[6].c_str());
	bool isTop = atoi(tokens[7].c_str());

	Stair* obj = new Stair() ;
	y = titlemap->getWorldHeight() - y;
	obj->SetPosition(x, y);
	obj->setWidth(width);
	obj->setHeight(height);
	obj->setRightTop(isRight, isTop);
	objects.push_back(obj);
}
void CPlayScene::_ParseSection_GRID(string line)
{
	
	vector<string> tokens = split(line);
	if (tokens.size() < 1) return;
	string path = tokens[0];
	grid.init(path);
	

}
void CPlayScene::Load()
{
	
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);
	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line == "[SPACE]") {
			section = SCENE_SECTION_SPACE; continue;
		}
		if (line == "[STAIR]") {
			section = SCENE_SECTION_STAIR; continue;
		}
		if (line == "[GRID]") {
			section = SCENE_SECTION_GRID; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	
		
		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_SPACE: _ParseSection_SPACE(line); break;
			case SCENE_SECTION_STAIR: _ParseSection_STAIR(line); break;
			case SCENE_SECTION_GRID:  _ParseSection_GRID(line); break;
		}
	}

	f.close();

	//CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	setCurentSpace(0);
	
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}


void AddObjectToCamara(vector<LPGAMEOBJECT>* objectsInCamara, LPGAMEOBJECT obj)
{
	for (size_t i = 0; i < objectsInCamara->size(); i++)
	{
		if (objectsInCamara->at(i) == obj) {
			return;
		}
	}
	objectsInCamara->push_back(obj);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	//vector<LPGAMEOBJECT> coObjects;
	objectsInCamara.clear();
	grid.checkCellColitionCamera(Camera::getInstance());
	vector<int> tempIndexObject = grid.getInxInCamera();
	for (int j = 0; j < tempIndexObject.size(); j++) {
		int k = tempIndexObject[j];
		LPGAMEOBJECT obj = objects[k];
		if (obj->getAlive())
		{
			AddObjectToCamara(&objectsInCamara, obj);
			//objectsInCamara.push_back(obj);
		}
	}
	
	for (size_t i = 0; i < objectsInCamara.size(); i++)
	{
		objectsInCamara[i]->Update(dt, &objectsInCamara);
	}
	for (int j = 0; j < addtionalObject.size(); j++) {
		if(addtionalObject[j]->isAlive)
			addtionalObject[j]->Update(dt, &objectsInCamara);
	}
	if (player == NULL)
		return;
	player->Update(dt, &objectsInCamara);
	Weapon::getInstance()->Update(dt, &objectsInCamara);
	ScoreBar::getInstance()->update();
	Camera::getInstance()->update();
}

void CPlayScene::Render()
{
	titlemap->render(Camera::getInstance());
	for (int i = 0; i < objectsInCamara.size(); i++)
		objectsInCamara[i]->Render();

	for (int j = 0; j < addtionalObject.size(); j++) {
		addtionalObject[j]->Render();
	}
	player->Render();
	Weapon::getInstance()->Render();
	ScoreBar::getInstance()->render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	objects.clear();
	objectsInCamara.clear();
	player = NULL;
	CTextures::GetInstance()->Clear(texturesID);
	CSprites::GetInstance()->Clear(spritesID);
	CAnimations::GetInstance()->Clear(animationsID);
	CAnimationSets::GetInstance()->Clear(animationSetsID);
	texturesID.clear();
	spritesID.clear();
	animationsID.clear();
	animationSetsID.clear();
	addtionalObject.clear();

}

void CPlayScene::addAddtionalObject(LPGAMEOBJECT obj)
{
	addtionalObject.push_back(obj);
}

vector<LPGAMEOBJECT> CPlayScene::getAddtionalObject()
{
	return addtionalObject;
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{

}


void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	Simon* simon = ((CPlayScene*)scence)->player;
	CGame *game = CGame::GetInstance();
	simon->isRightDown = game->IsKeyDown(DIK_RIGHT);
	simon->isLeftDown = game->IsKeyDown(DIK_LEFT);
	simon->isDownDown = game->IsKeyDown(DIK_DOWN);
	simon->isUpDown = game->IsKeyDown(DIK_UP);;
	simon->isJump = game->IsKeyDown(DIK_X);
	simon->isJumpDown = simon->isJump && !simon->isPreviousJumpDown;
	simon->isPreviousJumpDown = simon->isJump;
	simon->isAttackDown = game->IsKeyDown(DIK_Z);
	simon->isAttack = simon->isAttackDown && !simon->isPreviousAttackDown;
	simon->isPreviousAttackDown = simon->isAttackDown;
	simon->switchScene1 = game->IsKeyDown(DIK_1);
	simon->switchScene2 = game->IsKeyDown(DIK_2);
	simon->switchScene3 = game->IsKeyDown(DIK_3);
	simon->switchScene4 = game->IsKeyDown(DIK_4);


}