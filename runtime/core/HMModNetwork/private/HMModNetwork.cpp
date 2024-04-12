#include "HMModNetwork.h"
#include"Utility.hpp"

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
			EventManager::GetEvent<const char*,int, AsyncReceiveDataCallBackBinary,HPROTOCOL&>
				(TSTR("CreateTCPClient"))
				.Add(std::bind(&HMModNetwork::CreateTCPClient,this,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
			EventManager::GetEvent<HPROTOCOL, HMArray<uint8_t>&>
				(TSTR("SendData"))
				.Add(std::bind(&HMModNetwork::SendData, this, std::placeholders::_1, std::placeholders::_2));
			return true;
		}

		void HMModNetwork::Terminate()
		{
			m_pNetworkMod->Terminate();
		}

		void HMModNetwork::CreateTCPClient(const char* serverIP, int port, AsyncReceiveDataCallBackBinary callbackfunc,HPROTOCOL& protocolID)
		{
			protocolID = m_pNetworkMod->CreateTCPClient(serverIP, port, callbackfunc);
		}

		void HMModNetwork::SendData(HPROTOCOL handle, HMArray<uint8_t>& data)
		{
			m_pNetworkMod->SendData(handle, data);
		}
	}
}