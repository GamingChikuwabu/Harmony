#include"GameObject.h"
#include<iostream>

namespace HARMONY
{
	namespace CORE
	{
		HM_MANUAL_REGISTER_DERIVED_CLASS_BODY_PROPERTIES(GameObject)
			HM_ADD_PROPERTY_CLASS(GameObject, _transform),
			HM_ADD_PROPERTY_STRING(GameObject, _name),
			HM_ADD_PROPERTY_STRING(GameObject, _tag),
			HM_ADD_PROPERTY_STRING(GameObject, _layer),
			HM_ADD_PROPERTY_ARRAY(GameObject, m_componentList)
		HM_MANUAL_REGISTER_DERIVED_CLASS_BODY_PROPERTIES_END(GameObject, HMObject)

		GameObject::GameObject()
		:_transform()
		{
			
		}
		GameObject::~GameObject()
		{
			
		}
	}
}