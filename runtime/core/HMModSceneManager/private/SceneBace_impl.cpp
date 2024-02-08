#include"SceneBace_impl.h"

namespace HARMONY
{
	namespace CORE
	{
		SceneBase_impl::SceneBase_impl()
		{
		}
		SceneBase_impl::~SceneBase_impl()
		{
		}
		const char* SceneBase_impl::GetName()
		{
			return _sceneName.c_str();
		}
		const char* SceneBase_impl::GetGuid()
		{
			return _sceneGuid.c_str();
		}
		void SceneBase_impl::Update()
		{
			for (auto subscene : _subSceneList)
			{
				subscene->Update();
			}
		}
		void SceneBase_impl::Render(const std::vector<ICommandBuffer*>& commandBuffers)
		{
			for (auto subscene : _subSceneList)
			{
				subscene->Render(commandBuffers);
			}
		}
		
		std::shared_ptr<SceneBase> SceneBase_impl::FindSceneFromGUID(const char* guid) {
			//// 検索対象のGUIDが無効な場合、空のshared_ptrを返す
			//if (guid == nullptr) {
			//	return nullptr;
			//}

			//// 現在のSceneBaseオブジェクトのGUIDが一致するかチェック
			//if (_sceneGuid == guid) {
			//	return std::shared_ptr<SceneBase>(this); 
			//}

			//// _subSceneList を探索
			//for (auto& weakScene : _subSceneList) {
			//	auto scene = weakScene.lock();
			//	if (scene) {
			//		if (scene->GetGuid() == guid) {
			//			return scene;
			//		}

			//		// サブシーン内を再帰的に検索
			//		auto foundScene = scene->FindSceneFromGUID(guid);
			//		if (foundScene) {
			//			return foundScene;
			//		}
			//	}
			//}

			//// GUIDが一致するSceneが見つからない場合、空のshared_ptrを返す
			return nullptr;
		}
		bool SceneBase_impl::AddSceneObject(std::shared_ptr<SceneBase> child_scene)
		{
			_subSceneGuids.push_back(child_scene->GetGuid());
			_subSceneList.push_back(child_scene);
			return true;
		}
	}
}