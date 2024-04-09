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