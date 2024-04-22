#include"RootScene.h"

namespace HARMONY
{
	namespace CORE
	{
		HM_MANUAL_REGISTER_DERIVED_CLASS_BODY_PROPERTIES(RootScene)
			HM_ADD_PROPERTY_ARRAY(RootScene, _uiScene),
			HM_ADD_PROPERTY_ARRAY(RootScene, _dbScene)
		HM_MANUAL_REGISTER_DERIVED_CLASS_BODY_PROPERTIES_END(RootScene,SceneBase_impl)
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
		void RootScene::Render(const HMArray<ICommandBuffer*>& commandBuffers)
		{
			SceneBase_impl::Render(commandBuffers);
		}
	}
}