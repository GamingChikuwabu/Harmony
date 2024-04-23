#include"HMModSceneManager.h"
#include"HMJson.h"
#include"HMMetaFile.h"
#include"Scene.h"
#include"SceneBace_impl.h"
#include"RootScene.h"
#include"EventManager.h"
#include"LogManager.h"
#include <fstream>
#include<filesystem>
#include"Serializer.hpp"

namespace HARMONY
{
	namespace CORE
	{
		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(HMModSceneManager)
			HM_ADD_PROPERTY_OBJECT(HMModSceneManager, _Scenes)
		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(HMModSceneManager)

		RegisterModuleClass(HMModSceneManager)
		HMModSceneManager::HMModSceneManager()
		{
			
		}

		HMModSceneManager::~HMModSceneManager()
		{

		}

		bool HMModSceneManager::AwakeInitialize()
		{
			//パスを取得
			auto path =  ModuleManager::GetAllAssetsRootPath();
			//シーンのメタファイルを取得
			auto scenePath = FindMetaFileWithGUID(path,GetRootSceneGuid().GetRaw());
			{
				auto scenefile = RemoveMetaExtension(scenePath).GetRaw();
				CreateScene(scenePath.c_str());
			}
			
			return true;
		}

		void HMModSceneManager::Terminate()
		{
			
		}

		void HMModSceneManager::LoadScene(std::filesystem::path scenefilepath, SceneBase* parentscene, uint32_t type)
		{
			
		}

		void HMModSceneManager::CreateScene(const TCHAR* path)
		{
			_Scenes = CreateObject<RootScene>();
			Ifstream ifs(path);
			SERIALIZER::IJsonArchiver ij(ifs);
			ij& _Scenes;
			//シーンのロードイベントを送信
			SERIALIZER::OJsonArchiver oja;
			auto jsonStr = oja & _Scenes;
			EventManager::GetEvent<const TCHAR*>(TSTR("LoadedScene")).Broadcast(jsonStr.GetRaw());
		}

		SceneBase* HMModSceneManager::GetScene()
		{
			return _Scenes;
		}

		const HMString HMModSceneManager::GetRootSceneGuid()
		{
			HMString path = HMString(ModuleManager::GetProjectAssetsPath()) + HMString(TSTR("/config")) + HMString(TSTR("/sceneroot.json"));
			auto rawpath = path.GetRaw();
			Document doc;
			Ifstream ifs(rawpath);
			if (ifs)
			{
				StreamWrapper isw(ifs);
				doc.ParseStream(isw);
				if (!doc.HasParseError() && doc.HasMember(TSTR("guid")))
				{
					return HMString(doc[TSTR("guid")].GetString());
				}
			}
			return nullptr;
		}
	}
}