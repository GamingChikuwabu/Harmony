#pragma once
#include"ModuleManager.h"
#include"Utility.hpp"
#include<filesystem>
#include<Scene.h>

namespace HARMONY
{
	namespace CORE
	{
		class HMMODSCENEMANAGER_API HMModSceneManager: public IModule
		{
			HM_MANUAL_REGISTER_BASE_CLASS_BODY(HMModSceneManager)
		public:
			/// @brief コンストラクタ
			HMModSceneManager();
			/// @brief デストラクタ
			~HMModSceneManager();
			/// @brief 初期化関数
			/// @return 結果
			bool AwakeInitialize()override;

			/// @brief 終了処理
			void Terminate()override;

			/// @brief 新しいシーンを作成しロードする 
			/// @param scenefilepath シーンファイルのパス
			void CreateScene(const TCHAR* path);

			SceneBase* GetScene();


		private:
			void LoadScene(std::filesystem::path scenefilepath,SceneBase* parentscene,uint32_t type);
			const HMString GetRootSceneGuid();
			SceneBase* _Scenes;
		};
	}
} /// namespace HARMONY