#pragma once
#include "Rect.h"
#include"CollitionType.h"
/* đây là lớp Rect có thể di chuyển */
class MovableRect :
	public Rect
{
	/* độ dời di chuyển của đối tượng */
	float dx, dy;
	COLLISION_TYPE collisionType;
	bool stopCollision;
public:
	COLLISION_TYPE getCollisionType();
	void setCollisionType(COLLISION_TYPE collisionType);
	virtual void setDx(float dx);
	virtual void setDy(float dy);
	float getDx();
	float getDy();
	void goX();
	void goY();

	/* phương thức xử lý va chạm là phương thức ảo sẽ được mỗi đối tượng override để hiện thực */
	virtual void onCollision(MovableRect* other, float collisionTime, int nx, int ny);

	bool getStopCollision();
	void setStopCollision(bool stopCollision);

	MovableRect();
	~MovableRect();
};

