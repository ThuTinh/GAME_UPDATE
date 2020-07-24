#include"Stair.h"
#include "Simon.h"

void Stair::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Simon* player = Simon::getInstance();
	bool isUpDown = player->isUpDown;
	bool isDownDown = player->isDownDown;
	if (AABBCheck(player))
	{
		if (isUpDown)
		{
			if (
				!isTop &&
				player->getIsOnGround() &&
				player->getState() == SIMON_STATE_NORMAL
				)
			{

				if (isRightStair)
				{
					player->setX(getMidX() - player->getWidth());
					player->setY(getBottom() + player->getHeight());
				}
				else
				{
					player->setX(getMidX());
					player->setY(getBottom() + player->getHeight());
				}

				player->setStartStair();
				player->aniIndex = SIMON_ANI_ASCEND_STAIRS;
				player->setPauseAnimation(true);
				player->setStairDirection(isRightStair ? 1 : 0);

			}
		}
		if (isDownDown)
		{
			if (
				isTop &&
				player->getIsOnGround() &&
				player->getState() == SIMON_STATE_NORMAL
				)
			{
				if (isRightStair)
				{
					player->setX(getX() - 8);
					player->setY(getBottom() + player->getHeight());
				}
				else
				{
					player->setX(getMidX());
					player->setY(getBottom() + player->getHeight());
				}
				player->setStartStair();
				player->aniIndex = SIMON_ANI_DESCEN_STAIRS;
				player->setPauseAnimation(true);
				player->setStairDirection(isRightStair ? 1 : 0);

			}
		}

		if (player->getState() == SIMON_STATE_ON_STAIR)
		{
			if (
				player->getDy() == 1 &&
				this->isTop
				)
			{
				player->setIsLastRunStair(true);
			}
			if (
				player->getDy() == -1 &&
				!this->isTop
				
				)
			{
				player->setIsLastRunStair(true);
			}
		}
	}

}

void Stair::setRightTop(bool isRightStair, bool isTop)
{
	this->isRightStair = isRightStair;
	this->isTop = isTop;
}

Stair::Stair()
{
	setCollitionType(COLLISION_TYPE_STAIR);
}

Stair::~Stair()
{
}