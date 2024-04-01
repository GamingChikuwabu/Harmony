#include "HMModNetwork.h"
#include "EventManager.h"
#include "LogManager.h"

namespace HARMONY
{
	namespace CORE
	{
		RegisterModuleClass(HMModNetwork);
		HMModNetwork::HMModNetwork():m_pNetworkMod(nullptr)
		{
		}

		HMModNetwork::~HMModNetwork()
		{
		}

		bool HMModNetwork::AwakeInitialize()
		{
			m_pNetworkMod = ModuleManager::GetModule<INetWorkModule>();
			HM_ASSERT(m_pNetworkMod != nullptr,"ネットワークモジュールの取得に失敗");
			EventManager::GetEvent<const char*,int, DataReceivedCallback,HPROTOCOL&>
				(TEXT("CreateTCPClient"))
				.Add(std::bind(&HMModNetwork::CreateTCPClient,this,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
			EventManager::GetEvent<HPROTOCOL, std::vector<char>&>
				(TEXT("SendData"))
				.Add(std::bind(&HMModNetwork::SendData, this, std::placeholders::_1, std::placeholders::_2));
			return true;
		}

		void HMModNetwork::Terminate()
		{

		}

		void HMModNetwork::CreateTCPClient(const char* serverIP, int port, DataReceivedCallback callbackfunc,HPROTOCOL& protocolID)
		{
			protocolID = m_pNetworkMod->CreateTCPClient(serverIP, port, callbackfunc);
		}

		void HMModNetwork::SendData(HPROTOCOL handle, std::vector<char>& data)
		{
			m_pNetworkMod->SendData(handle, data);
		}
	}
}