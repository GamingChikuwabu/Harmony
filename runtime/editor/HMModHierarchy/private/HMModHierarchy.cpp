#include"HMModHierarchy.h"
#include"HMModIPCManager.h"
#include"LogManager.h"
#include"Scene.h"
#include"HierarchyMassage.h"

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
			IPC->RegisterCallBack(IPC->GetCommandInfo("AddGameObject").id, std::bind(&HMModHierarchy::AddGameObject, this, std::placeholders::_1));
			IPC->RegisterCallBack(IPC->GetCommandInfo("CreateSceneObject").id, std::bind(&HMModHierarchy::CreateSceneObject, this, std::placeholders::_1));
			return true;
		}

		void HMModHierarchy::CreateSceneObject(const std::vector<char>& data)
		{
			SceneData receive_data;
			// 最初に全体のデータをコピー
			memcpy(&receive_data, data.data(), sizeof(SceneData));
			HM_DEBUG_LOG("white", TSTR("名前:%s,GUID:%s"), receive_data._name,receive_data._guid);
			_sceneManager->CreateRootScene(receive_data._name, receive_data._guid); 
			SendAddedSceneData(receive_data._name, "root");
		}

		void HMModHierarchy::AddSceneObject(const std::vector<char>& data)
		{
			
		}

		void HMModHierarchy::SendAddedSceneData(const char* name, const char* parent_name)
		{
			auto IPC = ModuleManager::GetModule<HMModIPCManager>();

			// SendSceneData 構造体の初期化
			SceneData send_data = {};

			// 安全な文字列コピーを使用して name と parent_name をコピー
			strncpy_s(send_data._name, name, sizeof(send_data._name));
			send_data._name[sizeof(send_data._name) - 1] = '\0';  // null終端の確保

			strncpy_s(send_data._parentGuid, parent_name, sizeof(send_data._parentGuid));
			send_data._parentGuid[sizeof(send_data._parentGuid) - 1] = '\0';  // null終端の確保

			// 適切なコマンドIDを取得し、データを送信
			IPC->SendData(IPC->GetCommandInfo("AddedScene").id, send_data);
		}

		void HMModHierarchy::AddGameObject(const std::vector<char>& data)
		{
			
		}
	}
}