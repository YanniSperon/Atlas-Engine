#include "Object.h"

Atlas::Object::Object(E_ObjectType objectType)
	: type(objectType)
{

}

Atlas::Object::Object(const Object& obj2)
	: type(obj2.type)
{

}

Atlas::Object::~Object()
{

}

Atlas::Object::E_ObjectType Atlas::Object::GetType()
{
	return type;
}
