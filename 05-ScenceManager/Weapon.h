#pragma once
#include"GameObject.h"
#define WEAPON_ANI_W11 0
#define WEAPON_ANI_W12	1
#define WEAPON_ANI_W13	2
#define WEAPON_ANI_W21	3
#define WEAPON_ANI_W22	4
#define WEAPON_ANI_W23	5
#define WEAPON_ANI_W31	6
#define WEAPON_ANI_W32	7
#define WEAPON_ANI_W33	8
#define WEAPON_ANI_W41	9
#define WEAPON_ANI_W42 10	
#define WEAPON_ANI_W43 11
#define WEAPON_ANI_W51	12
#define WEAPON_ANI_W52	13
#define WEAPON_ANI_W53	14
#define WEAPON_ANI_W61	15
#define WEAPON_ANI_W62 16	
#define WEAPON_ANI_W63 17

class Weapon : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	static Weapon* instance;
	static Weapon* getInstance();
	Weapon();
	~Weapon();



};

