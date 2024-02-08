#pragma once
#include"SceneBace_impl.h"

namespace HARMONY
{
	namespace CORE
	{
		class DynamicScene : public SceneBase_impl
		{
		public:
			DynamicScene();
			~DynamicScene();
			void Update()override;
			void Render(const std::vector<ICommandBuffer*>& commandBuffers)override;
		protected:
			
		};
	}
}