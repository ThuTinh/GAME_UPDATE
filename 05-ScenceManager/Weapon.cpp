#include"Weapon.h"
#include"Simon.h"

Weapon* Weapon::instance = 0;
void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (Simon::getInstance()->aniIndex != SIMON_ANI_STAND_USING_SUB && Simon::getInstance()->aniIndex != SIMON_ANI_DUCK_USING_SUB) {
		setAlive(false);
	}
}

void Weapon::Render()
{
	if (Simon::getInstance()->aniIndex == SIMON_ANI_STAND_USING_SUB || Simon::getInstance()->aniIndex == SIMON_ANI_DUCK_USING_SUB) {
		if (Simon::getInstance()->getDirection() == DIRECTION_RIGHT) {
			setDirection(DIRECTION::DIRECTION_RIGHT);
			switch (Simon::getInstance()->frameIndex)
			{
			case 0:
				setY(Simon::getInstance()->getY() + 2);
				setX(Simon::getInstance()->getX()-5);
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
				default:
					aniIndex = WEAPON_ANI_W41;
					break;
				}
				break;
			case 1:
				setY(Simon::getInstance()->getY() + 3);
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
				default:
					aniIndex = WEAPON_ANI_W42;
					break;
				}

				break;
			default:
				setY(Simon::getInstance()->getY() + 2);
				setX(Simon::getInstance()->getX() + 20);
				switch (Simon::getInstance()->getNumberArchery())
				{
				case 0:
					setX(Simon::getInstance()->getX() + 18);
					aniIndex = WEAPON_ANI_W13;
					break;
				case 1:
					aniIndex = WEAPON_ANI_W23;
					break;
				case 2:
					aniIndex = WEAPON_ANI_W33;
					break;
				default:
					aniIndex = WEAPON_ANI_W43;
					break;
				}


				break;
			};


		}
		else
		{
			setDirection(DIRECTION::DIRECTION_LEFT);
			switch (Simon::getInstance()->frameIndex)
			{
			case 0:
				setY(Simon::getInstance()->getY());
				setX(Simon::getInstance()->getX()+ 20);
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
				default:
					aniIndex = WEAPON_ANI_W41;
					break;
				}

				break;

			case 1:
				setY(Simon::getInstance()->getY());
				setX(Simon::getInstance()->getX() + 15);
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
				default:
					aniIndex = WEAPON_ANI_W42;
					break;
				}


				break;
			default:
				setY(Simon::getInstance()->getY() + 2);
				setX(Simon::getInstance()->getX() - 30);
				switch (Simon::getInstance()->getNumberArchery())
				{
				case 0:
					setX(Simon::getInstance()->getX() -20);
					aniIndex = WEAPON_ANI_W13;
					break;
				case 1:
					aniIndex = WEAPON_ANI_W23;
					break;
				case 2:
					aniIndex = WEAPON_ANI_W33;
					break;
				default:
					aniIndex = WEAPON_ANI_W43;
					break;
				}
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
}

Weapon::~Weapon()
{
}
