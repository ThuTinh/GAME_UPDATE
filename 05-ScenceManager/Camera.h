#pragma once
#include"MovableRect.h"
#include"Space.h"
class Camera : public MovableRect
{
	static Camera* instance;

	Space* space;

public:
	static Camera* getInstance();

	void convertWorldToView(float xWorld, float yWorld, float& xView, float& yView);

	void setSpace(Space* space);
	Space* getSpace();
	void update();

	Camera();
	~Camera();
};

