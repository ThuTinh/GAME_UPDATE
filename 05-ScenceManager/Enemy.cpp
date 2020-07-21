#include "Enemy.h"
#include"Simon.h"
#include"Gound.h"
#include "Weapon.h"
#include"ScoreBar.h"
#include"Die-affect.h"
#include "Game.h"
#include "BigHeart.h"
#include <stdlib.h>
#include "SubWeaponAttack.h"
void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	///* mặc định là false cho tới khi chạm sàn */
	if (AABBCheck(Simon::getInstance()) ) {
		if (Simon::getInstance()->state != SIMON_STATE_ON_STAIR) {
			if (!Simon::getInstance()->isDie()) {
				Simon::getInstance()->setHurt(getDirection(), getX());
			}
		}
		else
		{
			Simon::getInstance()->setHurtInStair();
		}
	}
	if (CGame::GetInstance()->GetCurrentScene()->getAddtionalObject().size() > 0) {
		vector<LPGAMEOBJECT> listObject = CGame::GetInstance()->GetCurrentScene()->getAddtionalObject();
		for (size_t i = 0; i < listObject.size(); i++)
		{
			if (dynamic_cast<SubWeaponAttack*>(listObject[i]) && listObject[i]->isAlive) {
				if (AABBCheck(listObject[i])) {
					setAlive(false);
					ScoreBar::getInstance()->increaseScore(ENEMY_SCORE);
					makeDieEffect();
					int r = rand();
					if (r % 2 == 0) {
						BigHeart* bigHeart = new BigHeart();
						bigHeart->animation_set = CAnimationSets::GetInstance()->Get(ID_ANI_HEART);
						CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(bigHeart);
						bigHeart->setX(getMidX());
						bigHeart->setY(getMidY());
						bigHeart->setAlive(true);
					}
				}
			}
		}
	}
	CGameObject::Update(dt);
}

void Enemy::Render()
{
	animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
}

void Enemy::onCollision(CGameObject* other, float collisionTime, int nx, int ny)
{
	CGameObject::onCollision(other, collisionTime, nx, ny);
	
}

void Enemy::setDirectionFollowPlayer()
{
	if (Simon::getInstance()->getMidX() - getMidX() < 0)
	{
		setDirection(DIRECTION_LEFT);
	}
	else
	{
		setDirection(DIRECTION_RIGHT);
	}
}

void Enemy::onPlayerContact()
{
	
}

void Enemy::restorePosition()
{
	CGameObject::restorePosition();
}

Enemy::Enemy()
{
	setCollitionType(COLLISION_TYPE_ENEMY);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	collisionDelay.init(100);
}

Enemy::~Enemy()
{
	setVx(0);
}