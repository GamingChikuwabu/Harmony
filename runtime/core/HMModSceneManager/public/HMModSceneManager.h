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

			/// @brief 現在読み込まれているシーンをすべてシリアライズする関数
			void SerializeAllScene();

			/// @brief 引数のシーンをシリアライズする
			/// @param scene シリアライズするシーン
			void SerializeScene(SceneBase* scene);

			/// @brief 名前検索でrootのシーンを取得する関数
			/// @return rootのシーン
			SceneBase* GetRootSceneFromName(const char* name);

			/// @brief GUID検索でrootシーンを取得する関数
			/// @param guid 
			/// @return シーンオブジェクト
			SceneBase* GetRootSceneFromGuid(const char* guid);

			/// @brief ルートのシーンを追加する関数
			/// @param name シーンの名前
			/// @param guid シーンのguid
			void CreateRootScene(const char* name,const char* guid);

			/// @brief GUIDからオブジェクトを探す関数
			/// @param guid guid
			/// @return 見つかったオブジェクト
			SceneBase* FindSceneFromGUID(const char* guid);
		private:
			void LoadScene(std::filesystem::path scenefilepath,SceneBase* parentscene,uint32_t type);
			HMArray<SceneBase*> _rootScenes;
		};
	}
}