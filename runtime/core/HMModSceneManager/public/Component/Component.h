#pragma once
#include"HMObject.h"
#include"Component.generate.h"

namespace HARMONY
{
	namespace CORE
	{
		class GameObject;
		HMCLASS() 
		class HMMODSCENEMANAGER_API Component : public HMObject
		{
			HM_CLASS_BODY()
		public:
			Component():
			_gameObject(nullptr) {};
			virtual ~Component() {};
		protected:
			const GameObject* _gameObject;
			friend class GameObject;
		};
	}
}