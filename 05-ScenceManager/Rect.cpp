#include "Rect.h"
#include<Windows.h>
#include<string>

Rect::Rect()
{
	set(0, 0, 0, 0);
}

Rect::~Rect()
{
}

void Rect::moveX(float dx)
{
	setX(x + dx);
	//x = (int)(x + dx + 0.5);
	//OutputDebugString(std::to_string(dx + 0.5).c_str());
}

void Rect::moveY(float dy)
{
	setY(y + dy);
	//y = (int)(y + dy + 0.5);
}

void Rect::move(float dx, float dy)
{
	moveX(dx);
	moveY(dy);
}

float Rect::getX()
{
	return this->x;
}

float Rect::getY()
{
	return this->y;
}

float Rect::getWidth()
{
	return this->width;
}

float Rect::getHeight()
{
	return this->height;
}

void Rect::setX(float x)
{
	this->x = x;
}

void Rect::setY(float y)
{
	this->y = y;
}

void Rect::setWidth(float width)
{
	this->width = width;
}

void Rect::setHeight(float height)
{
	this->height = height;
}

void Rect::setLocation(float x, float y)
{
	setX(x);
	setY(y);
}

void Rect::setSize(float width, float height)
{
	setWidth(width);
	setHeight(height);
}

void Rect::set(float x, float y, float width, float height)
{
	setX(x);
	setY(y);
	setWidth(width);
	setHeight(height);
}

float Rect::getleft()
{
	return x;
}

float Rect::getRight()
{
	return x + width;
}

float Rect::getTop()
{
	return y;
}

float Rect::getBottom()
{
	return y - height;
}

float Rect::getMidX()
{
	return x + width / 2;
}

float Rect::getMidY()
{
	return y - height / 2;
}