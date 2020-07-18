#pragma once
class Rect
{
	float x, y, width, height;
public:
	void moveX(float dx);
	void moveY(float dy);
	void move(float dx, float dy);
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	virtual void setX(float x);
	virtual void setY(float y);
	virtual void setWidth(float width);
	virtual void setHeight(float height);
	void setLocation(float x, float y);
	void setSize(float width, float height);
	void set(float x, float y, float width, float height);
	float getleft();
	float getRight();
	float getTop();
	float getBottom();
	float getMidX();
	float getMidY();
	Rect();
	virtual ~Rect();
};

