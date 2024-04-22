#pragma once
#include"SceneBace_impl.h"

namespace HARMONY
{
	namespace CORE
	{
		class RootScene : public SceneBase_impl
		{
			HM_MANUAL_REGISTER_DERIVED_CLASS_BODY(RootScene,SceneBase_impl)
		public:
			RootScene();
			~RootScene();
			void Update()override;
			void Render(const HMArray<ICommandBuffer*>& commandBuffers)override;
		protected:
			HMArray<SceneBase*> _uiScene;
			HMArray<SceneBase*> _dbScene;
		};
	}
}