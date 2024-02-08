#pragma once
#include"StaticScene.h"

namespace HARMONY
{
	namespace CORE
	{
		class UIScene : public StaticScene
		{
		public:
			UIScene();
			~UIScene();
			void Update()override;
			void Render(const std::vector<ICommandBuffer*>& commandBuffers)override;
		};
	}
}