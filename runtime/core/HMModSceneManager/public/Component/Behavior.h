#pragma once
#include"Component.h"

namespace HARMONY
{
	namespace CORE
	{
		class Behavior : public Component
		{
		public:
			Behavior() :_IsEnable(true) {};
			~Behavior() {};

		private:
			bool _IsEnable;
		};
	}
}