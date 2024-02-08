#pragma once
#include"Scene.h"

namespace HARMONY
{
	namespace CORE
	{
		class SceneBase_impl : public SceneBase
		{
		public:
			SceneBase_impl();
			~SceneBase_impl();
			/// @brief シーンの名前を取得する関数
			/// @return シーンの名前
			virtual const char* GetName()override;

			/// @brief シーンのGUIDを取得する関数
			/// @return GUID
			virtual const char* GetGuid()override;

			/// @brief 更新関数
			virtual void Update()override;

			/// @brief 描画関数
			virtual void Render(const std::vector<ICommandBuffer*>& commandBuffers)override;

			virtual std::shared_ptr<SceneBase> FindSceneFromGUID(const char* guid)override;

			virtual bool AddSceneObject(std::shared_ptr<SceneBase> shild_scene)override;
		protected:
			std::string								_sceneName;
			std::string								_sceneGuid;
			std::list<std::string>					_subSceneGuids;
			std::list<std::shared_ptr<GameObject>>	_gameObjectList;
			std::list<std::shared_ptr<SceneBase>>	_subSceneList;
			std::list<std::shared_ptr<SceneBase>>   _dynamicScene;
			friend class HMModSceneManager;
		};
	}
}