#pragma once
#include "GameObject.h"
#define ITEM_GRAVITY -0.00002
enum ITEM_STATE
{
	ITEM_STATE_INVISIBLE,
	ITEM_STATE_VISIBLE,
	ITEM_STATE_PLAYER_EATED,
};
class Item : public CGameObject
{
	ITEM_STATE itemState;
	virtual void Render();

public:
	Item();
	virtual void SetState(int state);
	void setItemState(ITEM_STATE itemState);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	ITEM_STATE getItemState();
	virtual void onPlayerContact();
};