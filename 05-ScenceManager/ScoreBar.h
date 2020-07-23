#pragma once
#include"GameTime.h"
#include"Sprites.h"
#include "Animations.h"
#include"Item.h"

struct SCORE_LOCATION
{
	int X;
	int Y;
	int MaxLength;
};

enum TYPE_SUBWEAPON {
	SWORD,
	BOOMERANG,
	AXE,
	BLUEPOTION,
	STOPWATCH,
	DEFAUL,
};

class ScoreBar
{
	Item* subWeapon;
	TYPE_SUBWEAPON stypeSubweapon;
	LPANIMATION_SET animation_set;
	LPDIRECT3DTEXTURE9 scoreBar;
	void renderNumber(int num, int x, int y, int maxLength);
	void renderHealth();
	void renderBossHealth();
	void renderSubWeapon();
	void renderDoubleTripbleSub();
	static ScoreBar* instance;
	SCORE_LOCATION lifeLocation;
	SCORE_LOCATION heartLocation;
	SCORE_LOCATION stageLocation;
	SCORE_LOCATION scoreLocation;
	SCORE_LOCATION timeLocation;
	SCORE_LOCATION healthLocation;
	SCORE_LOCATION subWeaponLocation;
	SCORE_LOCATION bossHealthLocation;
	SCORE_LOCATION doubleSubLocation;

	int health;
	int bossHealth;
	int maxHealth;
	int playerLife;
	int heartCount;
	int currentStageNumber;
	int score;
	int time;
	GameTime timeGame;
	bool hasDoubleSub;
	bool hasTripleSub;
	void _ParseSection_TEXTURE_MISC(string line);
	void _ParseSection_TEXTURE_SCORE_BAR(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_LOCATION_LIFE(string line);
	void _ParseSection_LOCATION_HEART(string line);
	void _ParseSection_LOCATION_STAGE(string line);
	void _ParseSection_LOCATION_SCORE(string line);
	void _ParseSection_LOCATION_TIME(string line);
	void _ParseSection_LOCATION_HEALTHY(string line);
	void _ParseSection_LOCATION_SUBWEAPON(string line);
	void _ParseSection_LOCATION_BOSS_HEATHY(string line);
	void _ParseSection_LOCATION_DOUBLE_SUB(string line);
public:
	static ScoreBar* getInstance();
	ScoreBar();
	~ScoreBar();
	void render();
	void update();

	void setSubWeapon(Item* subWeapon);

	void setTypeSubWeapon(TYPE_SUBWEAPON type);
	TYPE_SUBWEAPON getTypeSubWeapon();
	void restoreHealth();
	void restoreBossHealth();

	int getPlayerLife();
	void setPlayerLife(int playerLife);
	void increasePlayerLife(int playerLife);

	int getHeartCount();
	void setHeartCount(int heartCount);
	void increaseHeartCount(int heartCount);

	int getScore();
	void setScore(int score);
	void increaseScore(int score);

	int getTime();
	void setTime(int time);
	void increaseTime(int time);

	int getHealth();
	void setHealth(int health);
	void increaseHealth(int health);

	int getBossHealth();
	void setBossHealth(int health);
	void increaseBossHealth(int health);

	int getMaxHealth();

	void setHasDoubleSub(bool has);
	void setHasTripbleSub(bool has);
	bool getHasDoubleSub();
	bool getHasTripleSub();
	void setCurrentStageNumber(int currentStageNumber);
	int getCurrentStageNumber();
	void Load(LPCWSTR sorebarFile);
};

