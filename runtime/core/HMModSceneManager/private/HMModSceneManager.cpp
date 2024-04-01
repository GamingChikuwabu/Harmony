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
			SERIALIZER::OJsonSerializer oj;
			auto dest = oj & obj;
			auto str = dest.GetRaw();
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
				SerializeScene(root.get());
			}
		}

		void HMModSceneManager::SerializeScene(SceneBase* scene)
		{
			
		}

		std::shared_ptr<SceneBase> HMModSceneManager::GetRootSceneFromName(const char* name)
		{
			return std::shared_ptr<SceneBase>();
		}

		std::shared_ptr<SceneBase> HMModSceneManager::GetRootSceneFromGuid(const char* guid)
		{
			return std::shared_ptr<SceneBase>();
		}

		void HMModSceneManager::CreateRootScene(const char* name, const char* guid)
		{
			_rootScenes.push_back(std::make_shared<RootScene>());
			static_cast<SceneBase_impl*>(_rootScenes.back().get())->_sceneName = name;
			static_cast<SceneBase_impl*>(_rootScenes.back().get())->_sceneGuid = guid;
			//static_cast<SceneBase_impl*>(_rootScenes.back().get())->_sceneType = SCENE_TYPE::Root;
		}

		void HMModSceneManager::LoadScene(std::filesystem::path scenefilepath, SceneBase* parentscene, uint32_t type)
		{
			
		}
	}
}