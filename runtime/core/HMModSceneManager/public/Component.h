#pragma once

namespace HARMONY
{
	namespace CORE
	{
		class GameObject;
		class Component
		{
		public:
			Component() {};
			virtual ~Component() {};
		protected:
			GameObject* _gameObject;
			friend class GameObject;
		};
	}
}