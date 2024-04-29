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
		:_IsSceneLoaded(false),
		_IsSceneUnLoaded(false),
		_nextSceneName(nullptr),
		_Scenes(nullptr)
		{
			
		}

		HMModSceneManager::~HMModSceneManager()
		{

		}

		bool HMModSceneManager::AwakeInitialize()
		{
			//フレームの最終処理時にシーンの状態を確認する
			EventManager::GetEvent<>(TSTR("OnFrameFinalized")).Add(std::bind(&HMModSceneManager::CheckSceneState, this));

			//パスを取得
			auto path =  ModuleManager::GetAllAssetsRootPath();
			//シーンのメタファイルを取得
			auto scenePath = FindMetaFileWithGUID(path,GetRootSceneGuid().GetRaw());
			//.metaの拡張子を削除
			auto scenefile = RemoveMetaExtension(scenePath).GetRaw();
			CreateScene(scenefile);
			return true;
		}

		void HMModSceneManager::Terminate()
		{
			
		}

		void HMModSceneManager::LoadScene(const TCHAR* sceneName)
		{
		}

		void HMModSceneManager::LoadSceneAdditive(const TCHAR* sceneName)
		{
		}

		void HMModSceneManager::SetActiveScene(const TCHAR* sceneName)
		{
		}

		void HMModSceneManager::UnloadScene(const TCHAR* sceneName)
		{
		}

		void HMModSceneManager::LoadScene(std::filesystem::path scenefilepath, SceneBase* parentscene, uint32_t type)
		{
			
		}

		void HMModSceneManager::CreateScene(const TCHAR* path)
		{
			if (path != nullptr)
			{
				_Scenes = CreateObject<RootScene>();
				Ifstream ifs(path);
				SERIALIZER::IJsonArchiver ij(ifs);
				ij & _Scenes;
				//シーンのロードイベントを送信
				SERIALIZER::OJsonArchiver oja;
				auto jsonStr = oja & _Scenes;
				EventManager::GetEvent<const TCHAR*>(TSTR("LoadedScene")).Broadcast(jsonStr.GetRaw());
			}
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
		void HMModSceneManager::CheckSceneState()
		{
			if (_IsSceneLoaded)
			{
				std::filesystem::path assetsRootDir = HMString(ModuleManager::GetProjectAssetsPath()).GetRaw();
				for (const auto& entry : std::filesystem::recursive_directory_iterator(assetsRootDir)) 
				{
					if (entry.is_regular_file() && entry.path().filename() == _nextSceneName) {
						CreateScene(entry.path().c_str());
						_nextSceneName = nullptr;
					}
				}
				if (_nextSceneName == nullptr)
				{
					_IsSceneLoaded = false;
					EventManager::GetEvent<>(TSTR("OnSceneLoaded")).Broadcast();
				}
			}
			if (_IsSceneUnLoaded)
			{

			}
		}
	}
} /// namespace HARMONY