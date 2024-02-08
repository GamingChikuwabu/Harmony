#pragma once
#include "SceneBace_impl.h"

namespace HARMONY
{
	namespace CORE
	{
		class StaticScene : public SceneBase_impl
		{
		public:
			StaticScene();
			~StaticScene();
			void Update()override;
			void Render(const std::vector<ICommandBuffer*>& commandBuffers)override;
		protected:

		};
	}
}