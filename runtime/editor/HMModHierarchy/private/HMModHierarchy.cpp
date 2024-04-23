#include"HMModHierarchy.h"
#include"HMModIPCManager.h"
#include"LogManager.h"
#include"Scene.h"


namespace HARMONY
{
	namespace EDITOR
	{
		RegisterModuleClass(HMModHierarchy)
		HMModHierarchy::HMModHierarchy()
		{
		}

		HMModHierarchy::~HMModHierarchy()
		{
		}

		bool HMModHierarchy::Initialize()
		{
			_sceneManager = ModuleManager::GetModule<CORE::HMModSceneManager>();
			HM_ASSERT(_sceneManager != nullptr, "シーンマネージャの取得に失敗");
			auto IPC = ModuleManager::GetModule<HMModIPCManager>();
			//IPC->RegisterCallBack(IPC->GetCommandInfo(TSTR("CreateSceneObject"))._id, std::bind(&HMModHierarchy::CreateSceneObject,this, std::placeholders::_1));
			//EventManager::GetEvent<HMString>(TSTR("LoadedScene")).Add(std::bind(&HMModHierarchy::CreateSceneObject, this, std::placeholders::_1));
			return true;
		}
	}
}