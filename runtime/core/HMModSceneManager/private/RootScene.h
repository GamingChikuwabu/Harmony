#pragma once
#include"SceneBace_impl.h"


namespace HARMONY
{
	namespace CORE
	{
		class RootScene : public SceneBase_impl
		{
		public:
			RootScene();
			~RootScene();
			void Update()override;
			void Render(const std::vector<ICommandBuffer*>& commandBuffers)override;
		protected:
			std::list<std::shared_ptr<SceneBase>> _uiScene;
			std::list<std::shared_ptr<SceneBase>> _dbScene;
		};
	}
}