#include "Gound.h"
#include "Light.h"
#include "Weapon.h"
#include"Simon.h"
#include "Game.h"
#include "BigHeart.h"
#include "SubWeaponAttack.h"
#include "Die-affect.h"
#include "Game.h"
void Light::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (AABBCheck(Weapon::getInstance()) && Weapon::getInstance()->getAlive()  && (Weapon::getInstance()->aniIndex ==2 || Weapon::getInstance()->aniIndex == 5 || Weapon::getInstance()->aniIndex == 8|| Weapon::getInstance()->aniIndex == 11 || Weapon::getInstance()->aniIndex == 14 || Weapon::getInstance()->aniIndex == 17) ) {
		setAlive(false);
		makeDieEffect();
	}
	if (CGame::GetInstance()->GetCurrentScene()->getAddtionalObject().size() > 0 && isAlive) {
		vector<LPGAMEOBJECT> listObject = CGame::GetInstance()->GetCurrentScene()->getAddtionalObject();
		for (size_t i = 0; i < listObject.size(); i++)
		{
			if (dynamic_cast<SubWeaponAttack*>(listObject[i]) && listObject[i]->isAlive) {
				if (AABBCheck(listObject[i])) {
					setAlive(false);
					makeDieEffect();
				}
			}
		}
	}
}

void Light::Render()
{
	if (isAlive)
		animation_set->at(0)->Render(x, y, frameIndex, DIRECTION_LEFT);
}

Light::Light()
{
	setCollitionType(COLLISION_TYPE_MISC);
	setPhysicsEnable(false);
}

void Light::SetState(int state)
{
}
