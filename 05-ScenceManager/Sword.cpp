#include "Sword.h"
#include"Simon.h"
#include"ScoreBar.h"
void Sword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Item::Update(dt, coObjects);
	if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		onPlayerContact();


	}
}

void Sword::onPlayerContact()
{
	//	Simon::getInstance()->setSubWeapon(this);
	//ScoreBar::getInstance()->setSubWeapon(this);
	ScoreBar::getInstance()->setTypeSubWeapon(TYPE_SUBWEAPON::SWORD);

}

Sword::Sword()
{
}

Sword::~Sword()
{
}