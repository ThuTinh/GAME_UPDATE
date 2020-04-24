#include"Stair.h"
#include "Simon.h"

void Stair::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	Simon* player = Simon::getInstance();
	bool isUpDown = player->isUpDown;
	bool isDownDown = player->isDownDown;
	/* nếu hiện tại đối tượng đang va chạm với player */
	if (AABBCheck(player))
	{
		/* nếu nhấn key lên */
		if (isUpDown)
		{

			if (
				/* stair hiện tại là stair dưới */
				!isTop &&
				/* nếu player ở trên ground */
				player->getIsOnGround() &&
				/* trạng thái hiện tại của player là bình thường */
				player->getState() == SIMON_STATE_NORMAL
				)
			{

				if (isRightStair)
				{
					/* đặt player đúng vị trí ban đầu. Tham khảo đối tượng stair trên world để xem */
					player->setX(getMidX() - player->getWidth());
					player->setY(getBottom() + player->getHeight());

				}
				else
				{
					/* đặt player đúng vị trí ban đầu. Tham khảo đối tượng stair trên world để xem */
					player->setX(getMidX());
					player->setY(getBottom() + player->getHeight());
				}

				/* stop tất cả chuyển động */
			/*	player->setVx(0);
				player->setVy(0);
				player->setDx(0);
				player->setDy(0);*/

				/* bắt đầu lên stair */
				player->setStartStair();

				/* set animation */
				player->aniIndex = SIMON_ANI_ASCEND_STAIRS;

				/* dừng chuyển động player */
				player->setPauseAnimation(true);

				/* set stair direction cho player */
				player->setStairDirection(isRightStair ? 1 : 0);

			}
		}

		/* nếu nhấn key xuống */
		if (isDownDown)
		{
			if (
				/* stair hiện tại là stair trên */
				isTop &&
				/* nếu player ở trên ground */
				player->getIsOnGround() &&
				/* trạng thái hiện tại của player là bình thường */
				player->getState() == SIMON_STATE_NORMAL
				)
			{
				if (isRightStair)
				{
					/* đặt player đúng vị trí ban đầu. Tham khảo đối tượng stair trên world để xem */
					player->setX(getX() - 8);
					player->setY(getBottom() + player->getHeight());
				}
				else
				{
					/* đặt player đúng vị trí ban đầu. Tham khảo đối tượng stair trên world để xem */
					player->setX(getMidX());
					player->setY(getBottom() + player->getHeight());
				}

				/* stop tất cả chuyển động */
				/*player->setVx(0);
				player->setVy(0);
				player->setDx(0);
				player->setDy(0);*/

				/* bắt đầu lên stair */
				player->setStartStair();

				/* set animation */
				player->aniIndex = SIMON_ANI_DESCEN_STAIRS;

				/* dừng chuyển động player */
				player->setPauseAnimation(true);

				/* set stair direction cho player */
				player->setStairDirection(isRightStair ? 1 : 0);

			}
		}

		/* nếu player state là ở stair */
		if (player->getState() == SIMON_STATE_ON_STAIR)
		{
			if (
				/* player đang đi lên */
				player->getDy() == 1 &&
				/* gặp cục stair chặn trên */
				this->isTop
				)
			{
				player->setIsLastRunStair(true);
			}
			if (
				/* player đang đi xuống */
				player->getDy() == -1 &&
				/* gặp cục stair chặn dưới */
				!this->isTop
				
				)
			{
				player->setIsLastRunStair(true);
			}
		}
	}

	//BaseObject::onUpdate(dt);
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