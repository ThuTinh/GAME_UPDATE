﻿#include "MovableRect.h"

void MovableRect::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
}


COLLISION_TYPE MovableRect::getCollisionType()
{
	return this->collisionType;
}
void MovableRect::setCollisionType(COLLISION_TYPE collisionType)
{
	this->collisionType = collisionType;
}

bool MovableRect::getStopCollision()
{
	return this->stopCollision;
}
void MovableRect::setStopCollision(bool stopCollision)
{
	this->stopCollision = stopCollision;
}

MovableRect::MovableRect()
{
	dx = 0;
	dy = 0;
}

void MovableRect::setDx(float dx)
{
	this->dx = dx;
}
void MovableRect::setDy(float dy)
{
	this->dy = dy;
}
float MovableRect::getDx()
{
	return dx;
}
float MovableRect::getDy()
{
	return dy;
}

void MovableRect::goX()
{
	Rect::moveX(dx);
}

void MovableRect::goY()
{
	Rect::moveY(dy);
}

MovableRect::~MovableRect()
{
}
