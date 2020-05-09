//#include "AdditionalObject.h"
//#include "Camera.h"
//
//
//unordered_map<int, AdditionalObject*>* AdditionalObject::objects = 0;
//unordered_map<int, AdditionalObject*>* AdditionalObject::getObjects()
//{
//	if (objects == 0)
//		objects = new unordered_map<int, AdditionalObject*>();
//	return objects;
//}
//
//void AdditionalObject::objectsUpdate()
//{
//	for (size_t i = 0; i < getObjects()->size(); i++)
//	{
//		auto o = objects->at(i);
//		//o->performUpdate();
//		if (o->needDelete)
//		{
//			objects->erase(i);
//			i--;
//		}
//	}
//	for (size_t i = 0; i < getObjects()->size(); i++)
//	{
//		auto o = objects->at(i);
//		o->update(0);
//	}
//}
//
//void AdditionalObject::objectsRender(Camera* cam)
//{
//	for (size_t i = 0; i < getObjects()->size(); i++)
//	{
//		auto o = objects->at(i);
//		o->animation_set->at(o->aniIndex)->Render(o->x, o->y, o->frameIndex, o->direction, o->pauseAnimation);
//		
//	}
//}
//
//void AdditionalObject::setNeedDelete(bool needDelete)
//{
//	this->needDelete = needDelete;
//}
//
//
//void AdditionalObject::update(float dt)
//{
//	
//	CGameObject::Update(dt);
//}
//
//AdditionalObject::AdditionalObject()
//{
//	objects[5] = *this;
//	setNeedDelete(false);
//}
//
//
//AdditionalObject::~AdditionalObject()
//{
//}
