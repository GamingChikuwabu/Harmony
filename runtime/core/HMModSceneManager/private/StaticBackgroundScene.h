#pragma once
#include"DynamicScene.h"

namespace HARMONY
{
	namespace CORE
	{
		class StaticBackgroundScene : public DynamicScene
		{
		public:
			StaticBackgroundScene();
			~StaticBackgroundScene();
			void Update()override;
			void Render(const std::vector<ICommandBuffer*>& commandBuffers)override;
		};
	}
}