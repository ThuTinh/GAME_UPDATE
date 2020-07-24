#include "Gound.h"
#include "explore-effect.h"
#include "Weapon.h"
#include"Simon.h"
#include"Animations.h"
void ExploreEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timeDelay.update();
	if (timeDelay.isTerminated())
	{
		setAlive(false);
	}
}

void ExploreEffect::Render()
{
	if (isAlive) {
		animation_set->at(INDEX_EXPLORE)->Render(x, y, frameIndex, DIRECTION_LEFT);
	}
}

ExploreEffect::ExploreEffect()
{
	timeDelay.init(TIMEDELAY);
	animation_set = CAnimationSets::GetInstance()->Get(IDANI_EXPLORE);
	setAlive(false);
	setPhysicsEnable(true);
	
}

