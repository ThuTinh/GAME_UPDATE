#pragma once
#include"Enemy.h"
#define ZOOMBIE_SCORE 100
#define ZOOMBIE_RUN_DX 200
#define ZOOMBIE_RUN_VX 0.035
#define ZOOMBIE_RUN_DX_TO_TURNING 400
#define ZOOMBIE_GRAVITY -0.00003
enum ZOOMBIE_STATE
{
	ZOOMBIE_STAND,
	ZOOMBIE_RUN,
	ZOOMBIE_RUN_TURNING

};
class Zoombie : public Enemy
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	Zoombie();
	~Zoombie();

private:

};

