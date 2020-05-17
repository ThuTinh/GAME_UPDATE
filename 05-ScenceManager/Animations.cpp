#include "Animations.h"
#include "Utils.h"
#include"Camera.h"

CAnimationSets * CAnimationSets::__instance = NULL;

LPANIMATION_FRAME CAnimation::getFrame(int index)
{
	return frames.at(index);
}

void CAnimation::setCurrentFrame(int frameIndex)
{
	this->currentFrame = frameIndex;
}

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);

	if (sprite == NULL)
	{
		DebugOut(L"[ERROR] Sprite ID %d cannot be found!\n", spriteId);
	}

	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

// NOTE: sometimes Animation object is NULL ??? HOW ??? 
void CAnimation::Render(float x, float y, int &frameIndex, DIRECTION direction, bool pauseAnimation ,int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			if (!pauseAnimation) {
				currentFrame++;
				lastFrameTime = now;
				if (currentFrame == frames.size()) currentFrame = 0;
				frameIndex = currentFrame;
			}
		
		}
	}
	float xView, yView;
	Camera::getInstance()->convertWorldToView(x, y, xView, yView);
	frames[currentFrame]->GetSprite()->Draw(xView, yView, direction, alpha);
}

void CAnimation::RenderScoreBar(float x, float y, int frameIndex, DIRECTION direction)
{
	float xView, yView;
	//Camera::getInstance()->convertWorldToView(x, y, xView, yView);
	frames[frameIndex]->GetSprite()->Draw(x, y, direction);
} 



CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	LPANIMATION ani = animations[id];
	if (ani == NULL)
		DebugOut(L"[ERROR] Failed to find animation id: %d\n", id);
	return ani;
}

void CAnimations::Clear(vector<int> anisID)
{
	for (size_t i = 0; i < anisID.size(); i++)
	{
		LPANIMATION ani = Get(anisID.at(i));
		delete ani;
		animations.erase(anisID.at(i));
	}
}

CAnimationSets::CAnimationSets()
{

}

CAnimationSets *CAnimationSets::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimationSets();
	return __instance;
}

LPANIMATION_SET CAnimationSets::Get(unsigned int id)
{
	LPANIMATION_SET ani_set = animation_sets[id];
	if (ani_set == NULL)
		DebugOut(L"[ERROR] Failed to find animation set id: %d\n",id);
	 
	return ani_set;
}

void CAnimationSets::Clear(vector<int> listId)
{
	for (size_t i = 0; i < listId.size(); i++)
	{
		LPANIMATION_SET ani = Get(listId.at(i));
		delete ani;
		animation_sets.erase(listId.at(i));
	}
}

void CAnimationSets::Add(int id, LPANIMATION_SET ani_set)
{
	animation_sets[id] = ani_set;
}
