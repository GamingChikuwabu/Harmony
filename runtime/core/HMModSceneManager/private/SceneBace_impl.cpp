#include"SceneBace_impl.h"

namespace HARMONY
{
	namespace CORE
	{
		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(SceneBase_impl)
			HM_ADD_PROPERTY_STRING(SceneBase_impl, _sceneName),
			HM_ADD_PROPERTY_STRING(SceneBase_impl, _sceneGuid),
			HM_ADD_PROPERTY_ARRAY(SceneBase_impl, _subSceneGuids),
		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(SceneBase_impl)
		SceneBase_impl::SceneBase_impl()
		{
		}
		SceneBase_impl::~SceneBase_impl()
		{
		}
		const TCHAR* SceneBase_impl::GetName()
		{
			return _sceneName.GetRaw();
		}
		const TCHAR* SceneBase_impl::GetGuid()
		{
			return _sceneGuid.GetRaw();
		}

		void SceneBase_impl::Update()
		{
			for (auto subscene : _subSceneList)
			{
				subscene->Update();
			}
		}

		void SceneBase_impl::Render(const HMArray<ICommandBuffer*>& commandBuffers)
		{
			for (auto subscene : _subSceneList)
			{
				subscene->Render(commandBuffers);
			}
		}

		bool SceneBase_impl::AddSceneObject(SceneBase* shild_scene)
		{
			_subSceneGuids.Add(shild_scene->GetGuid());
			_subSceneList.Add(shild_scene);
			return false;
		}
	}
}