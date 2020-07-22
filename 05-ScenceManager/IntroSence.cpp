#include <iostream>
#include <fstream>
#include "IntroSence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include"Gound.h"
#include "AirPlane.h"
#include"GateIntro.h"
#include"IntroBat.h"
#include"KeyStart.h"
#include"Mountain.h"

using namespace std;

IntroSence::IntroSence(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new IntroScenceKeyHandler(this);
	titlemap = new Tilemap();
}

void IntroSence::setCurentSpace(int spaceID)
{
	this->currentSpace = spaces[spaceID];
	Camera::getInstance()->setSpace(this->currentSpace);
	Camera::getInstance()->setLocation(getCurentSpace()->CameraX, getCurentSpace()->CameraY);
	player->SetPosition(getCurentSpace()->PlayerX, getCurentSpace()->PlayerY);
}

Space* IntroSence::getCurentSpace()
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
#define SCENE_SECTION_GRID 10

#define OBJECT_TYPE_GROUND	-1
#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_MOUNTAIN 100
#define OBJECT_TYPE_KEYSTART 101
#define OBJECT_TYPE_GATE_INTRO -100
#define OBJECT_TYPE_BAT_INTRO 201
#define OBJECT_TYPE_PLANE 200

#define MAX_SCENE_LINE 1024


void IntroSence::_ParseSection_TEXTURES(string line)
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

void IntroSence::_ParseSection_SPRITES(string line)
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
	CSprites::GetInstance()->Add(ID, x, y, with, height, anchorX, anchorY, anchorXRight, anchorYRight, tex);
}

void IntroSence::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}
	animationsID.push_back(ani_id);
	CAnimations::GetInstance()->Add(ani_id, ani);
}

void IntroSence::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

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
void IntroSence::_ParseSection_OBJECTS(string line)
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

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

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
	case OBJECT_TYPE_PLANE: obj = new AirPlane(); break;
	case OBJECT_TYPE_GATE_INTRO: obj = new GateIntro(); break;
	case OBJECT_TYPE_BAT_INTRO: {
		obj = new IntroBat();
		if (x < 90) {
			obj->setDirection(DIRECTION_RIGHT);
		}
		else
		{
			obj->setDirection(DIRECTION_LEFT);
		}
		break;
	} 
	case OBJECT_TYPE_KEYSTART: obj = new KeyStart(); break;
	case OBJECT_TYPE_MOUNTAIN: obj = new Mountain(); break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	y = titlemap->getWorldHeight() - y;
	obj->SetPosition(x, y);
	obj->setWidth(width);
	obj->setHeight(height);
	obj->initBox.set(x, y, width, height);
	if (ani_set_id != -1) {
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	}
	objects.push_back(obj);
}

void IntroSence::_ParseSection_MAP(string line) {
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;
	titlemap->Init(atoi(tokens[0].c_str()), tokens[1]);

}
void IntroSence::_ParseSection_SPACE(string line)
{
	Space* tempSpace = new Space();
	vector<string> tokens = split(line);
	if (tokens.size() < 9) return;
	int id = atoi(tokens[0].c_str());
	tempSpace->X = atoi(tokens[1].c_str());
	tempSpace->Y = atoi(tokens[2].c_str());
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


void IntroSence::Load()
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
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line == "[SPACE]") {
			section = SCENE_SECTION_SPACE; continue;
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
		}
	}

	f.close();

	//CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	setCurentSpace(0);

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void IntroSence::Update(DWORD dt)
{
	
	for (size_t i = 0; i < objects.size(); i++)
	{
 		objects[i]->Update(dt, &objects);
	}
	if (player == NULL)
		return;
	player->Update(dt, &objects);
	Camera::getInstance()->update();

}

void IntroSence::Render()
{
	titlemap->render(Camera::getInstance());
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	if(player != NULL)
		player->Render();
	if(CGame::GetInstance()->current_scene != -1)
		ScoreBar::getInstance()->render();
}

/*
	Unload current scene
*/
void IntroSence::Unload()
{
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	objects.clear();
	player = NULL;
	CTextures::GetInstance()->Clear(texturesID);
	CSprites::GetInstance()->Clear(spritesID);
	CAnimations::GetInstance()->Clear(animationsID);
	CAnimationSets::GetInstance()->Clear(animationSetsID);
	texturesID.clear();
	spritesID.clear();
	animationsID.clear();
	animationSetsID.clear();

}

void IntroSence::setStopUpdate(bool stop)
{
}

bool IntroSence::getStopUpdate()
{
	return false;
}

void IntroSence::addAddtionalObject(LPGAMEOBJECT obj)
{
}

vector<LPGAMEOBJECT> IntroSence::getAddtionalObject()
{
	return vector<LPGAMEOBJECT>();
}

void IntroScenceKeyHandler::OnKeyDown(int KeyCode)
{

}

void IntroScenceKeyHandler::OnKeyUp(int KeyCode)
{

}


void IntroScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	game->isStartGame = game->IsKeyDown(DIK_W) || game->IsKeyDown(DIK_SPACE);

}