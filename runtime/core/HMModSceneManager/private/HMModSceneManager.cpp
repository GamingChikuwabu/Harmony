#include"HMModSceneManager.h"
#include"HMJson.h"
#include"HMMetaFile.h"
#include"Scene.h"
#include"DynamicScene.h"
#include"UIScene.h"
#include"DBScene.h"
#include "StaticBackgroundScene.h"
#include"SceneBace_impl.h"
#include"RootScene.h"
#include"EventManager.h"
#include"LogManager.h"
#include <fstream>
#include"Serializer.hpp"

namespace HARMONY
{
	namespace CORE
	{
		RegisterModuleClass(HMModSceneManager)
		HMModSceneManager::HMModSceneManager()
		{

		}

		HMModSceneManager::~HMModSceneManager()
		{

		}

		bool HMModSceneManager::AwakeInitialize()
		{
			HMObject* obj = new Component();
			auto prop = HMObject::StaticGetClass()->GetPropertyByName(L"vec");

			SERIALIZER::OJsonArchiver oj;
			auto dest = oj & obj;
			auto str = dest.GetRaw();
			std::wofstream fileStream(L"GameObject.json");
			if (fileStream.is_open()) {
				// 文字列をファイルに書き込む
				fileStream << str;
				// ファイルストリームを閉じる
				fileStream.close();
			}
			else {
				// ファイルオープンに失敗した場合の処理
				std::wcerr << L"ファイルを開けませんでした: " << std::endl;
			}
			/*HMObject* obj2 = nullptr;
			SERIALIZER::IJsonArchiver ij(str);
			ij & obj2;*/

			printf("");

			/*std::filesystem::path path = ModuleManager::GetProjectAssetsPath();
			path.append("config").append("sceneroot.json");
			auto json_string =  LoadJson(path.string().c_str());
			std::string guid = json_string["guid"].GetString();
			if (guid != "")
			{
				auto scene_file_meta_path = FindMetaFileWithGUID(ModuleManager::GetAllAssetsRootPath(), guid);
				auto sceneType = LoadJson(scene_file_meta_path.string().c_str())["type"].GetInt();
				auto scene_file_path = RemoveMetaExtension(scene_file_meta_path);
				LoadScene(scene_file_path,nullptr, sceneType);
				return true;
			}*/
			return true;
		}

		void HMModSceneManager::Terminate()
		{
			SerializeAllScene();
		}

		void HMModSceneManager::SerializeAllScene()
		{
			for (auto root : _rootScenes)
			{
				SerializeScene(root);
			}
		}

		void HMModSceneManager::SerializeScene(SceneBase* scene)
		{
			
		}

		SceneBase* HMModSceneManager::GetRootSceneFromName(const char* name)
		{
			return nullptr;
		}

		SceneBase* HMModSceneManager::GetRootSceneFromGuid(const char* guid)
		{
			return nullptr;
		}

		void HMModSceneManager::CreateRootScene(const char* name, const char* guid)
		{
			
		}

		void HMModSceneManager::LoadScene(std::filesystem::path scenefilepath, SceneBase* parentscene, uint32_t type)
		{
			
		}
	}
}