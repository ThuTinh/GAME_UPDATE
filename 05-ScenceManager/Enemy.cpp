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
	//vy += ENEMY_GRAVITY * dt;
	//if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive() && isAlive) {
	//	setAlive(false);
	//	ScoreBar::getInstance()->increaseScore(ENEMY_SCORE);
	//	DieEffect *dieEffect = new DieEffect();
	//	CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(dieEffect);
	//	dieEffect->setX(getMidX());
	//	dieEffect->setY(getMidY());
	//	dieEffect->setAlive(true);
	//	dieEffect->timeDelay.start();
	//	int r = rand();
	//	if (r % 2 !=0) {
	//		BigHeart *bigHeart = new BigHeart();
	//		bigHeart->animation_set = CAnimationSets::GetInstance()->Get(ID_ANI_HEART);
	//		CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(bigHeart);
	//		bigHeart->setX(getMidX());
	//		bigHeart->setY(getMidY());
	//		bigHeart->setAlive(true);
	//	}
	//}
	//CGameObject::Update(dt);
	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();

	//// turn off collision when die 
	//if (isAlive)
	//	CalcPotentialCollisions(coObjects, coEvents);


	//// No collision occured, proceed normally
	//if (coEvents.size() == 0)
	//{
	//	x += dx;
	//	y += dy;
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;
	//	float rdx = 0;
	//	float rdy = 0;

	//	// TODO: This is a very ugly designed function!!!!
	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//	// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
	//	if (rdx != 0 && rdx != dx)
	//		x += nx * abs(rdx);

	//	// block every object first!

	//	x += min_tx * dx + nx * 0.4f;
	//	y += min_ty * dy + ny * 0.4f;

	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];
	//		if (!dynamic_cast<Ground*>(e->obj)) {
	//			x += dx;
	//		}
	//		else
	//		{
	//			onCollision(e->obj, e->t, e->nx, e->ny);

	//		}
	//	}
	//}
	////clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	///* mặc định là false cho tới khi chạm sàn */
	if (CGame::GetInstance()->GetCurrentScene()->getAddtionalObject().size() > 0) {
		vector<LPGAMEOBJECT> listObject = CGame::GetInstance()->GetCurrentScene()->getAddtionalObject();
		for (size_t i = 0; i < listObject.size(); i++)
		{
			if (dynamic_cast<SubWeaponAttack*>(listObject[i])) {
				if (AABBCheck(listObject[i])) {
					setAlive(false);
					ScoreBar::getInstance()->increaseScore(ENEMY_SCORE);
					DieEffect* dieEffect = new DieEffect();
					CGame::GetInstance()->GetCurrentScene()->addAddtionalObject(dieEffect);
					dieEffect->setX(getMidX());
					dieEffect->setY(getMidY());
					dieEffect->setAlive(true);
					dieEffect->timeDelay.start();
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

Enemy::Enemy()
{
	setCollitionType(COLLISION_TYPE_ENEMY);
	collitionTypeToCheck.push_back(COLLISION_TYPE_GROUND);
	collisionDelay.init(100);
}

Enemy::~Enemy()
{
}