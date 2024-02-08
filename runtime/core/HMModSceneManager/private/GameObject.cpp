#include"GameObject.h"
#include<iostream>

namespace HARMONY
{
	namespace CORE
	{
		GameObject::GameObject()
		:_transform(nullptr)
		{
			_transform = new Transform();
			static_cast<Component*>(_transform)->_gameObject = this;
		}
		GameObject::~GameObject()
		{
			delete _transform;
		}
	}
}