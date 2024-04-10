#pragma once
#include"Utility.hpp"

namespace HARMONY
{
	namespace CORE
	{
		class GameObject;
		HMCLASS() 
		class HMMODSCENEMANAGER_API Component : public HMObject
		{
			HM_MANUAL_REGISTER_DERIVED_CLASS_BODY(Component, HMObject)
		public:
			Component();
			virtual ~Component();
		protected:
			const GameObject* _gameObject;
			friend class GameObject;
		};
	}
}