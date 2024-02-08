#include"StaticScene.h"
namespace HARMONY
{
	namespace CORE
	{
		StaticScene::StaticScene()
		{

		}
		StaticScene::~StaticScene()
		{

		}
		void StaticScene::Update()
		{
			SceneBase_impl::Update();
		}
		void StaticScene::Render(const std::vector<ICommandBuffer*>& commandBuffers)
		{
			SceneBase_impl::Render(commandBuffers);
		}
	}
}