#pragma once
#include"Scene.h"
#include"HMString.h"

namespace HARMONY
{
	namespace CORE
	{
		class GameObject;
		class SceneBase_impl : public SceneBase
		{
			HM_MANUAL_REGISTER_BASE_CLASS_BODY(SceneBase_impl)
		public:
			SceneBase_impl();
			~SceneBase_impl();
			/// @brief シーンの名前を取得する関数
			/// @return シーンの名前
			virtual const TCHAR* GetName()override;

			/// @brief シーンのGUIDを取得する関数
			/// @return GUID
			virtual const TCHAR* GetGuid()override;

			/// @brief 更新関数
			virtual void Update()override;

			/// @brief 描画関数
			virtual void Render(const HMArray<ICommandBuffer*>& commandBuffers)override;

			virtual bool AddSceneObject(SceneBase* shild_scene)override;
		protected:
			HMString								_sceneName;
			HMString								_sceneGuid;
			HMArray<HMString>						_subSceneGuids;
			HMArray<GameObject*>					_gameObjectList;
			HMArray<SceneBase*>						_subSceneList;
			HMArray<SceneBase*>						_dynamicScene;
			friend class HMModSceneManager;
		};
	}
}