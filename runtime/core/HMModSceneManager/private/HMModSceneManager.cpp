#include"HMModSceneManager.h"
#include"HMJson.h"
#include"HMMetaFile.h"
#include"Scene.h"
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
		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(HMModSceneManager)
			HM_ADD_PROPERTY_OBJECT(HMModSceneManager, _rootScenes)
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
			_rootScenes = CreateObject<RootScene>();
			auto path =  ModuleManager::GetAllAssetsRootPath();
			auto scenePath = FindMetaFileWithGUID(path,GetRootSceneGuid().GetRaw());
			SERIALIZER::OJsonArchiver archiver;
			auto sceneData = archiver & _rootScenes;
			{
				auto scenefile = RemoveMetaExtension(scenePath).GetRaw();
				Ofstream ofs(scenefile);
				if (ofs)
				{
					ofs << sceneData.GetRaw();
				}
			}
			
			return true;
		}

		void HMModSceneManager::Terminate()
		{
			SerializeAllScene();
		}

		void HMModSceneManager::SerializeAllScene()
		{
			
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