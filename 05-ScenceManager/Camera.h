#pragma once
#include"MovableRect.h"
#include"Space.h"
/* camera là 1 hình chữ nhật có thể di chuyển nên sẽ kế thừa lại lớp MovableRect */
class Camera : public MovableRect
{
	static Camera* instance;

	Space* space;

public:
	static Camera* getInstance();

	void convertWorldToView(float xWorld, float yWorld, float& xView, float& yView);

	void setSpace(Space* space);
	Space* getSpace();
	/* cập nhật camera */
	void update();

	Camera();
	~Camera();
};

