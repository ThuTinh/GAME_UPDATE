#include "Archery.h"
#include"Simon.h"
 void Archery::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	 Item::Update(dt, coObjects);
	 if (AABBCheck(Simon::getInstance()) && getItemState() == ITEM_STATE_VISIBLE) {
		 Simon::getInstance()->aniIndex = SIMON_ANI_COLORS;
		 Simon::getInstance()->colorDelay.start();
	    setItemState(ITEM_STATE_PLAYER_EATED);
		setAlive(false);
		 this->onPlayerContact();
		 Simon::getInstance()->addNumberArchery(1);
	
	 }

}
 void Archery::onPlayerContact()
 {
 }
 Archery::Archery()
 {
 }

 Archery::~Archery()
 {
 }
