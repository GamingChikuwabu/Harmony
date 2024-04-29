#pragma once
#include"ModuleManager.h"
#include"Utility.hpp"
#include<filesystem>
#include<Scene.h>

namespace HARMONY
{
	namespace CORE
	{
		/// @brief シーンマネージャ
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

		public:
			/// @brief すべてのシーンを破棄し新しいシーンをロードする
			/// @param sceneName シーンの名前
			void LoadScene(const TCHAR* sceneName);

			/// @brief シーンを追加ロードする
			void LoadSceneAdditive(const TCHAR* sceneName);

			/// @brief 複数のシーンがある場合のプライマリシーンを設定する
			/// @param sceneName 設定するシーンの名前
			void SetActiveScene(const TCHAR* sceneName);

			/// @brief シーンをアンロードする
			/// @param sceneName 破棄するシーン名
			void UnloadScene(const TCHAR* sceneName);

			/// @brief 現在アクティブなシーンを取得する
			SceneBase* GetScene();
		private:
			/// @brief 新しいシーンを作成しロードする 
			/// @param scenefilepath シーンファイルのパス
			void CreateScene(const TCHAR* path);
			void LoadScene(std::filesystem::path scenefilepath,SceneBase* parentscene,uint32_t type);
			const HMString GetRootSceneGuid();
			void CheckSceneState();
		private:
			SceneBase* _Scenes;//シーンのリスト
			bool _IsSceneLoaded;//シーンをロードするフラグ
			bool _IsSceneUnLoaded;//シーンをアンロードするフラグ
			const TCHAR* _nextSceneName;//次ロードやアンロードするシーンの名前何もなければnullptr
		};
	} /// namespace CORE
} /// namespace HARMONY