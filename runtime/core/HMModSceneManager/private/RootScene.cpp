#include"RootScene.h"

namespace HARMONY
{
	namespace CORE
	{
		RootScene::RootScene()
		{
		}
		RootScene::~RootScene()
		{
		}
		void RootScene::Update()
		{
			SceneBase_impl::Update();
		}
		void RootScene::Render(const std::vector<ICommandBuffer*>& commandBuffers)
		{
			SceneBase_impl::Render(commandBuffers);
		}
	}
}