#include"Weapon.h"
#include"Simon.h"

Weapon* Weapon::instance = 0;
void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*if (Simon::getInstance()->aniIndex != SIMON_ANI_STAND_USING_SUB && Simon::getInstance()->aniIndex != SIMON_ANI_DUCK_USING_SUB) {
		setAlive(false);
	}*/
	setAlive(false);
}

void Weapon::Render()
{
	//Simon::getInstance()->aniIndex == SIMON_ANI_STAND_USING_SUB ||
	if (!Simon::getInstance()->isUseSub && (Simon::getInstance()->aniIndex == SIMON_ANI_STAND_USING_SUB || Simon::getInstance()->aniIndex == SIMON_ANI_DUCK_USING_SUB || Simon::getInstance()->aniIndex == SIMON_ANI_DESCEN_STAIRS_USING_SUB || Simon::getInstance()->aniIndex == SIMON_ANI_ASCEN_STAIRS_USING_SUB)) {
		if (Simon::getInstance()->getDirection() == DIRECTION_RIGHT) {
			setDirection(DIRECTION::DIRECTION_RIGHT);
			switch (Simon::getInstance()->frameIndex)
			{
			case 0:
				setY(Simon::getInstance()->getY()-7);
				setX(Simon::getInstance()->getX()-12);
				switch (Simon::getInstance()->getNumberArchery())
				{
				case 0:
					aniIndex = WEAPON_ANI_W11;
					break;
				case 1:
					aniIndex = WEAPON_ANI_W21;
					break;
				case 2:
					aniIndex = WEAPON_ANI_W31;
					break;
				case 3:
					aniIndex = WEAPON_ANI_W41;
					break;
				case 4:
					aniIndex = WEAPON_ANI_W51;
					break;
				default:
					aniIndex = WEAPON_ANI_W61;
					break;
				}
				break;
			case 1:
				setY(Simon::getInstance()->getY() );
				setX(Simon::getInstance()->getX() -5);
				switch (Simon::getInstance()->getNumberArchery())
				{
				case 0:
					aniIndex = WEAPON_ANI_W12;
					break;
				case 1:
					aniIndex = WEAPON_ANI_W22;
					break;
				case 2:
					aniIndex = WEAPON_ANI_W32;
					break;
				case 3:
					aniIndex = WEAPON_ANI_W42;
					break;
				case 4:
					aniIndex = WEAPON_ANI_W52;
					break;
				default:
					aniIndex = WEAPON_ANI_W62;
					break;
				}

				break;
			default:
				setY(Simon::getInstance()->getY()- 9 );
				setX(Simon::getInstance()->getX() + 16);
				switch (Simon::getInstance()->getNumberArchery())
				{
				case 0:
					//setX(Simon::getInstance()->getX() + 18);
					setY(Simon::getInstance()->getY() - 7);
					aniIndex = WEAPON_ANI_W13;
					break;
				case 1:
					aniIndex = WEAPON_ANI_W23;
					break;
				case 2:
					aniIndex = WEAPON_ANI_W33;
					break;
				case 3:
					aniIndex = WEAPON_ANI_W43;
					break;
				case 4:
					aniIndex = WEAPON_ANI_W53;
					break;
				default:
					aniIndex = WEAPON_ANI_W63;
					break;
				}
				setWidth(animation_set->at(aniIndex)->getFrame(0)->GetSprite()->getWidth());
				break;
			};


		}
		else
		{
			setDirection(DIRECTION::DIRECTION_LEFT);
			switch (Simon::getInstance()->frameIndex)
			{
			case 0:
				setY(Simon::getInstance()->getY()-8);
				setX(Simon::getInstance()->getX()+ 18);
				switch (Simon::getInstance()->getNumberArchery())
				{
				case 0:
					setX(Simon::getInstance()->getX() + 19);
					aniIndex = WEAPON_ANI_W11;
					break;
				case 1:
					setY(Simon::getInstance()->getY() - 9);
					aniIndex = WEAPON_ANI_W21;
					break;
				case 2:
					aniIndex = WEAPON_ANI_W31;
					break;
				case 3:
					aniIndex = WEAPON_ANI_W41;
					break;
				case 4:
					aniIndex = WEAPON_ANI_W51;
					break;
				default:
					aniIndex = WEAPON_ANI_W61;
					break;
				}
				break;

			case 1:
				setY(Simon::getInstance()->getY()-2);
				setX(Simon::getInstance()->getX() + 10);
				switch (Simon::getInstance()->getNumberArchery())
				{
				case 0:
					aniIndex = WEAPON_ANI_W12;
					break;
				case 1:
					aniIndex = WEAPON_ANI_W22;
					break;
				case 2:
					aniIndex = WEAPON_ANI_W32;
					break;
				case 3:
					aniIndex = WEAPON_ANI_W42;
					break;
				case 4:
					aniIndex = WEAPON_ANI_W52;
					break;
				default:
					aniIndex = WEAPON_ANI_W62;
					break;
				}
				break;
			default:
				setY(Simon::getInstance()->getY()-8);
				//setX(Simon::getInstance()->getX() - 40);
				setX(Simon::getInstance()->getX() -40);

				switch (Simon::getInstance()->getNumberArchery())
				{
				case 0:
					setX(Simon::getInstance()->getX() - 30);
					aniIndex = WEAPON_ANI_W13;
					break;
				case 1:
					setX(Simon::getInstance()->getX() - 30);
					setY(Simon::getInstance()->getY() - 9);
					aniIndex = WEAPON_ANI_W23;
					break;
				case 2:
					aniIndex = WEAPON_ANI_W33;
					break;
				case 3:
					aniIndex = WEAPON_ANI_W43;
					break;
				case 4:
					aniIndex = WEAPON_ANI_W53;
					break;
				default:
					aniIndex = WEAPON_ANI_W63;
					break;
				}
				setWidth(animation_set->at(aniIndex)->getFrame(0)->GetSprite()->getWidth());
				break;
			}
		}
		setAlive(true);
		animation_set->at(aniIndex)->Render(x, y, frameIndex, direction);
	}
}

Weapon* Weapon::getInstance()
{
	if (instance == 0) {
		instance = new Weapon();
	}
	return instance;
}

Weapon::Weapon()
{
	setAlive(false);
}

Weapon::~Weapon()
{
}
