#include"HMModSceneManager.h"
#include"HMJson.h"
#include"HMMetaFile.h"
#include"Scene.h"
#include"DynamicScene.h"
#include"UIScene.h"
#include"DBScene.h"
#include "StaticBackgroundScene.h"
#include"serialize.h"
#include"SceneBace_impl.h"
#include"RootScene.h"
#include"EventManager.h"
#include"LogManager.h"
#include <fstream>

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
			std::filesystem::path path = ModuleManager::GetProjectAssetsPath();
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
			}
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
			auto scene_file_meta_path = FindMetaFileWithGUID(ModuleManager::GetAllAssetsRootPath(), ((SceneBase_impl*)scene)->_sceneGuid); 
			auto scene_file_path = RemoveMetaExtension(scene_file_meta_path);
			//std::ofstream ofs(scene_file_path);
			//if (!ofs.is_open())
			//{
			//	return;
			//}
			//std::ostringstream os;
			//{
			//	boost::archive::xml_oarchive ar(os);
			//	switch (((SceneBase_impl*)scene)->_sceneType)
			//	{
			//	case SCENE_TYPE::Root:
			//		ar << boost::make_nvp("scene", *dynamic_cast<SceneBase_impl*>(scene));
			//		break;
			//	default:
			//		break;
			//	}
			//}
			//std::string s = os.str();
			//std::cout << s << std::endl;
			//ofs << s;
			//for (auto subscene : ((SceneBase_impl*)scene)->_subSceneList)
			//{
			//	if (subscene) {
			//		// リソースがまだ存在する
			//		SerializeScene(subscene.get());
			//	}
			//}
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
			//SceneBase_impl* root_scene = nullptr;
			//switch ((SCENE_TYPE)type)
			//{
			//case HARMONY::CORE::UI:
			//	root_scene = new UIScene();
			//	break;
			//case HARMONY::CORE::DB:
			//	root_scene = new DBScene();
			//	break;
			//case HARMONY::CORE::Dynamic:
			//	root_scene = new DynamicScene();
			//	break;
			//case HARMONY::CORE::StaticBackground:
			//	root_scene = new StaticBackgroundScene();
			//	break;
			//case HARMONY::CORE::Root:
			//	root_scene = new RootScene();
			//	break;
			//case HARMONY::CORE::MAX:
			//	break;
			//default:
			//	break;
			//}

			//std::ifstream ifs(scenefilepath);
			//if (ifs)
			//{
			//	//===========================================================================
			//	//デシリアライズ
			//	//===========================================================================
			//	std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
			//	std::istringstream is(str);
			//	try {
			//		boost::archive::xml_iarchive ar(is);
			//		ar >> boost::make_nvp("scene", *root_scene);
			//		HM_DEBUG_LOG("white", "%s", root_scene->GetName());
			//		//==========================================================================
			//		// ネスト構造を作成
			//		//==========================================================================
			//		if (parentscene != nullptr)//親オブジェクトがある場合
			//		{
			//			parentscene->AddSceneObject(std::shared_ptr<SceneBase_impl>(root_scene));
			//			for (auto& root : static_cast<SceneBase_impl*>(parentscene)->_subSceneGuids)
			//			{
			//				auto scene_file_meta_path = FindMetaFileWithGUID(ModuleManager::GetAllAssetsRootPath(), root);
			//				auto sceneType = LoadJson(scene_file_meta_path.string().c_str())["type"].GetInt();
			//				auto scene_file_path = RemoveMetaExtension(scene_file_meta_path);
			//				LoadScene(scene_file_path, _rootScenes.back().get(),sceneType); //再帰処理
			//			}
			//		}
			//		else//親オブジェクトがなくルートの場合
			//		{
			//			this->CreateRootScene(root_scene->_sceneName.c_str(), root_scene->_sceneGuid.c_str());
			//			for (auto& root : ((SceneBase_impl*)_rootScenes.back().get())->_subSceneGuids)
			//			{
			//				auto scene_file_meta_path = FindMetaFileWithGUID(ModuleManager::GetAllAssetsRootPath(), root);
			//				auto sceneType = LoadJson(scene_file_meta_path.string().c_str())["type"].GetInt();
			//				auto scene_file_path = RemoveMetaExtension(scene_file_meta_path);
			//				LoadScene(scene_file_path, _rootScenes.back().get(),type);//再帰処理
			//			}
			//		}
			//	}
			//	catch (const boost::archive::archive_exception& e) {
			//		std::cerr << "Sceneのデシリアライズに失敗: " << e.what() << std::endl;
			//		// デシリアライズに失敗したが、処理は続行する
			//	}
			//}
			//delete root_scene;
		}
	}
}