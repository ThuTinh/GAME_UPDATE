#include "Gound.h"
#include "ObjectBlack.h"
#include "Weapon.h"
#include"Simon.h"
#include "objectBlack-effect.h"
#include "Game.h"
void ObjectBlack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (checkOnlyOne)
		return;
	if (AABBCheck(Weapon::getInstance()) && (Weapon::getInstance()->aniIndex == 2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8 || Weapon::getInstance()->aniIndex == 11 || Weapon::getInstance()->aniIndex == 14 || Weapon::getInstance()->aniIndex == 17)) {
		checkOnlyOne = true;
		makeEfect();
		 Simon::getInstance()->addNumberObjectBlack(1);
		/*if (getY() <= YTEMP) {
			setY(YRENDER);
		}*/
		isRender = true;
	}

}

void ObjectBlack::Render()
{
	if (isRender)
	{
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
	}
}

void ObjectBlack::restorePosition()
{
	CGameObject::restorePosition();
	setPhysicsEnable(false);
	isRender = false;
	checkOnlyOne = false;
}

ObjectBlack::ObjectBlack()
{
	setCollitionType(COLLISION_TYPE_MISC);
	setPhysicsEnable(false);
	isRender = false;
	checkOnlyOne = false;
}

void ObjectBlack::SetState(int state)
{
}

void ObjectBlack::makeEfect()
{
	ObjectBlackEffect* effect1 = new ObjectBlackEffect();
	CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(effect1);
	effect1->setX(getMidX());
	effect1->setY(getMidY());
	effect1->setVx(-0.02);
	effect1->setVy(0.05);
	effect1->setAlive(true);
	effect1->timeDelay.start();

	ObjectBlackEffect* effect2 = new ObjectBlackEffect();
	CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(effect2);
	effect2->setX(getMidX()+ 5);
	effect2->setY(getMidY());
	effect2->setVx(-0.03);
	effect2->setVy(0.06);
	effect2->setAlive(true);
	effect2->timeDelay.start();

	ObjectBlackEffect* effect3 = new ObjectBlackEffect();
	CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(effect3);
	effect3->setX(getMidX()- 10);
	effect3->setY(getMidY());
	effect3->setVx(0.01);
	effect3->setVy(0.03);
	effect3->setAlive(true);
	effect3->timeDelay.start();
}
