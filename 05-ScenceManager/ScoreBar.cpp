#include "ScoreBar.h"
#include"Simon.h"
#include <fstream>
#include "Utils.h"
#include "Textures.h"
#include"Game.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_MAP	3
#define SCENE_SECTION_SPRITES 4
#define SCENE_SECTION_ANIMATIONS 5
#define SCENE_SECTION_ANIMATION_SETS 6
#define SCENE_SECTION_LOCATION_LIFE	7
#define SCENE_SECTION_LOCATION_SCORE 8
#define SCENE_SECTION_LOCATION_TIME	9
#define SCENE_SECTION_LOCATION_HEALTHY	10
#define SCENE_SECTION_LOCATION_SUBWEAPON	11
#define SCENE_SECTION_LOCATION_BOSS_HEATHY	12
#define SCENE_SECTION_LOCATION_STAGE	13
#define SCENE_SECTION_LOCATION_HEART	14
#define SCENE_SECTION_TEXTURE_MISC 15
#define SCENE_SECTION_TEXTURE_SCROE_BAR 16
#define MAX_SCENE_LINE 1024

#define MISC_SPRITE_ID_NUMBER 0
#define MISC_SPRITE_ID_LOST_HEALTH 1
#define MISC_SPRITE_ID_KNIFE 2
#define MISC_SPRITE_ID_BOOMERANG 3
#define NUMBER_WIDTH 8
#define HEALTH_WIDTH 4
void ignoreLineIfstream(ifstream & fs, int lineCount);


void ScoreBar::renderNumber(int num, int x, int y, int maxLength)
{
	int currentX = x + NUMBER_WIDTH * maxLength;
	int length = 0;
	while (num)
	{
		currentX -= NUMBER_WIDTH;
		int val = num % 10;
		animation_set->at(MISC_SPRITE_ID_NUMBER)->RenderScoreBar(currentX, y, val);
		num /= 10;
		length++;
	}
	for (; length < maxLength; length++)
	{
		currentX -= NUMBER_WIDTH;

		animation_set->at(MISC_SPRITE_ID_NUMBER)->RenderScoreBar(currentX, y, 0);
	}
}

void ScoreBar::renderHealth()
{
	int healthLost = maxHealth - health;
	int lastLocationXHealth = healthLocation.X + HEALTH_WIDTH * maxHealth - HEALTH_WIDTH;
	for (size_t i = 0; i < healthLost; i++)
	{
		animation_set->at(MISC_SPRITE_ID_LOST_HEALTH)->RenderScoreBar(lastLocationXHealth, healthLocation.Y, 0);
		lastLocationXHealth -= HEALTH_WIDTH;
	}
}

void ScoreBar::renderBossHealth()
{
	int healthLost = maxHealth - bossHealth;
	if (healthLost > maxHealth)
	{
		healthLost = maxHealth;
	}
	int lastLocationXHealth = bossHealthLocation.X + HEALTH_WIDTH * maxHealth - HEALTH_WIDTH;
	for (size_t i = 0; i < healthLost; i++)
	{
		animation_set->at(MISC_SPRITE_ID_LOST_HEALTH)->RenderScoreBar(lastLocationXHealth, healthLocation.Y, 0);
		lastLocationXHealth -= HEALTH_WIDTH;
	}
}

void ScoreBar::renderSubWeapon()
{
	//if (this->subWeapon != 0)
	//{
	//	/*this->subWeapon->getSprite()->render(subWeaponLocation.X,
	//		subWeaponLocation.Y,
	//		subWeapon->getAction(), 0);*/
	//	subWeapon->animation_set->at(0)->RenderScoreBar(subWeaponLocation.X, subWeaponLocation.Y, 0);

	//}

	switch (stypeSubweapon)
	{
	case SWORD:
		animation_set->at(MISC_SPRITE_ID_KNIFE)->RenderScoreBar(subWeaponLocation.X, subWeaponLocation.Y, 0);
		break;
	case BOOMERANG:
		animation_set->at(MISC_SPRITE_ID_BOOMERANG)->RenderScoreBar(subWeaponLocation.X, subWeaponLocation.Y, 0);
		break;
	default:
		break;
	}
}

ScoreBar* ScoreBar::instance = 0;
void ScoreBar::_ParseSection_TEXTURE_MISC(string line)
{

	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());
	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}
void ScoreBar::_ParseSection_TEXTURE_SCORE_BAR(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());
	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
	scoreBar = CTextures::GetInstance()->Get(texID);
}
void ScoreBar::_ParseSection_SPRITES(string line)
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

	CSprites::GetInstance()->Add(ID, x, y, with, height, anchorX, anchorY,anchorXRight, anchorYRight, tex);
}
void ScoreBar::_ParseSection_ANIMATIONS(string line)
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

	CAnimations::GetInstance()->Add(ani_id, ani);
}
void ScoreBar::_ParseSection_ANIMATION_SETS(string line)
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

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
	animation_set = s;

}
void ScoreBar::_ParseSection_LOCATION_LIFE(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return; // skip invalid lines
	lifeLocation.X = atoi(tokens[0].c_str());
	lifeLocation.Y = atoi(tokens[1].c_str());
	lifeLocation.MaxLength = atoi(tokens[2].c_str());
}
void ScoreBar::_ParseSection_LOCATION_HEART(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return; // skip invalid lines
	heartLocation.X = atoi(tokens[0].c_str());
	heartLocation.Y = atoi(tokens[1].c_str());
	heartLocation.MaxLength = atoi(tokens[2].c_str());
}

void ScoreBar::_ParseSection_LOCATION_STAGE(string line)
{

	vector<string> tokens = split(line);
	if (tokens.size() < 3) return; // skip invalid lines
	stageLocation.X = atoi(tokens[0].c_str());
	stageLocation.Y = atoi(tokens[1].c_str());
	stageLocation.MaxLength = atoi(tokens[2].c_str());

}
void ScoreBar::_ParseSection_LOCATION_SCORE(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return; // skip invalid lines
	scoreLocation.X = atoi(tokens[0].c_str());
	scoreLocation.Y = atoi(tokens[1].c_str());
	scoreLocation.MaxLength = atoi(tokens[2].c_str());
}
void ScoreBar::_ParseSection_LOCATION_TIME(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return; // skip invalid lines
	timeLocation.X = atoi(tokens[0].c_str());
	timeLocation.Y = atoi(tokens[1].c_str());
	timeLocation.MaxLength = atoi(tokens[2].c_str());
}
void ScoreBar::_ParseSection_LOCATION_HEALTHY(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return; // skip invalid lines
	healthLocation.X = atoi(tokens[0].c_str());
	healthLocation.Y = atoi(tokens[1].c_str());
	maxHealth = atoi(tokens[2].c_str());
	setHealth(maxHealth);
	setBossHealth(maxHealth);
}
void ScoreBar::_ParseSection_LOCATION_SUBWEAPON(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return; // skip invalid lines
	subWeaponLocation.X = atoi(tokens[0].c_str());
	subWeaponLocation.Y = atoi(tokens[1].c_str());

}
void ScoreBar::_ParseSection_LOCATION_BOSS_HEATHY(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return; // skip invalid lines
	bossHealthLocation.X = atoi(tokens[0].c_str());
	bossHealthLocation.Y = atoi(tokens[1].c_str());
	bossHealthLocation.MaxLength = atoi(tokens[2].c_str());
}
ScoreBar* ScoreBar::getInstance()
{
	if (instance == 0)
		instance = new ScoreBar();
	return instance;
}

ScoreBar::ScoreBar()
{

	timeGame.init(1000);
	setPlayerLife(2);
	setScore(0);
	setHeartCount(5);
	setHealth(maxHealth);
	setBossHealth(maxHealth);
	setTime(900);
	currentStageNumber = 1;
	setSubWeapon(0);
	stypeSubweapon = DEFAUL;

}


ScoreBar::~ScoreBar()
{
}

void ScoreBar::render()
{
	//scoreBar->Render(0, 0, 0);
	CGame::GetInstance()->Draw(0,0,0,0, scoreBar,0,0,255,40);
	renderNumber(getPlayerLife(), lifeLocation.X, lifeLocation.Y, lifeLocation.MaxLength);
	renderNumber(getHeartCount(), heartLocation.X, heartLocation.Y, heartLocation.MaxLength);
	renderNumber(currentStageNumber, stageLocation.X, stageLocation.Y, stageLocation.MaxLength);
	renderNumber(score, scoreLocation.X, scoreLocation.Y, scoreLocation.MaxLength);
	renderNumber(time, timeLocation.X, timeLocation.Y, timeLocation.MaxLength);
	renderHealth();
	renderBossHealth();
	renderSubWeapon();
}

void ScoreBar::update()
{
	if (timeGame.atTime())
	{
		increaseTime(-1);
	}
}

void ScoreBar::setSubWeapon(Item* subWeapon)
{
	this->subWeapon = subWeapon;
}

void ScoreBar::setTypeSubWeapon(TYPE_SUBWEAPON type)
{
	this->stypeSubweapon = type;
}

TYPE_SUBWEAPON ScoreBar::getTypeSubWeapon()
{
	return stypeSubweapon;
}



void ScoreBar::restoreHealth()
{
	setHealth(maxHealth);
}

void ScoreBar::restoreBossHealth()
{
	setBossHealth(maxHealth);
}

int ScoreBar::getPlayerLife()
{
	return playerLife;
}

void ScoreBar::setPlayerLife(int playerLife)
{
	if (playerLife >= 0)
		this->playerLife = playerLife;
}

void ScoreBar::increasePlayerLife(int playerLife)
{
	setPlayerLife(this->playerLife + playerLife);
}

int ScoreBar::getHeartCount()
{
	return heartCount;
}

void ScoreBar::setHeartCount(int heartCount)
{
	this->heartCount = heartCount;
}

void ScoreBar::increaseHeartCount(int heartCount)
{
	setHeartCount(this->heartCount + heartCount);
}

void ScoreBar::setCurrentStageNumber(int currentStageNumber)
{
	this->currentStageNumber = currentStageNumber;
}

int ScoreBar::getCurrentStageNumber()
{
	return currentStageNumber;
}

void ScoreBar::Load(LPCWSTR sorebarFile)
{
	DebugOut(L"[INFO] Start loading scorebar resources from : %s \n", sorebarFile);

	ifstream f;
	f.open(sorebarFile);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines
		if (line[0] == '/' && line[1] == '/') continue;	// skip comment lines

		if (line == "[TEXTURE_MISC]") { section = SCENE_SECTION_TEXTURE_MISC; continue; }
		if (line == "[TEXTURE_SCORE_BAR]") { section = SCENE_SECTION_TEXTURE_SCROE_BAR; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[LOCATION_LIFE]") {
			section = SCENE_SECTION_LOCATION_LIFE; continue;
		}
		if (line == "[LOCATION_HEART_COUNT]") {
			section = SCENE_SECTION_LOCATION_HEART; continue;
		}
		if (line == "[LOCATION_SCORE]") {
			section = SCENE_SECTION_LOCATION_SCORE; continue;
		}
		if (line == "[LOCATION_HEALTH]") {
			section = SCENE_SECTION_LOCATION_HEALTHY; continue;
		}
		if (line == "[LOCATION_SUBWEAPON]") {
			section = SCENE_SECTION_LOCATION_SUBWEAPON; continue;
		}
		if (line == "[LOCATION_TIME]") {
			section = SCENE_SECTION_LOCATION_TIME; continue;
		}
		if (line == "[LOCATION_BOSS_HEATHY]") {
			section = SCENE_SECTION_LOCATION_BOSS_HEATHY; continue;
		}
		if (line == "[LOCATION_STAGE]") {
			section = SCENE_SECTION_LOCATION_STAGE; continue;
		}

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURE_MISC: _ParseSection_TEXTURE_MISC(line); break;
		case SCENE_SECTION_TEXTURE_SCROE_BAR: _ParseSection_TEXTURE_SCORE_BAR(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_LOCATION_LIFE: _ParseSection_LOCATION_LIFE(line); break;
		case SCENE_SECTION_LOCATION_HEART: _ParseSection_LOCATION_HEART(line); break;
		case SCENE_SECTION_LOCATION_SCORE: _ParseSection_LOCATION_SCORE(line); break;
		case SCENE_SECTION_LOCATION_HEALTHY: _ParseSection_LOCATION_HEALTHY(line); break;
		case SCENE_SECTION_LOCATION_TIME: _ParseSection_LOCATION_TIME(line); break;
		case SCENE_SECTION_LOCATION_STAGE: _ParseSection_LOCATION_STAGE(line); break;
		case SCENE_SECTION_LOCATION_BOSS_HEATHY: _ParseSection_LOCATION_BOSS_HEATHY(line); break;
		case SCENE_SECTION_LOCATION_SUBWEAPON: _ParseSection_LOCATION_SUBWEAPON(line); break;

		}
	}
}

int ScoreBar::getScore()
{
	return score;
}
void ScoreBar::setScore(int score)
{
	this->score = score;
}
void ScoreBar::increaseScore(int score)
{
	this->score += score;
}

int ScoreBar::getTime()
{
	return time;
}
void ScoreBar::setTime(int time)
{
	if (time >= 0)
		this->time = time;
}
void ScoreBar::increaseTime(int time)
{
	setTime(this->time + time);
}

int ScoreBar::getHealth()
{
	return health;
}
void ScoreBar::setHealth(int health)
{
	if (health >= 0)
		this->health = health;
}
void ScoreBar::increaseHealth(int health)
{
	setHealth(this->health + health);
}

int ScoreBar::getBossHealth()
{
	return bossHealth;
}
void ScoreBar::setBossHealth(int health)
{
	this->bossHealth = health;
}
void ScoreBar::increaseBossHealth(int health)
{
	setBossHealth(bossHealth + health);
}

int ScoreBar::getMaxHealth()
{
	return maxHealth;
}
