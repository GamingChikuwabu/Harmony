#include"AsioTCPIPClient.h"
#include"HMBoostAsio.h"
#include"ModuleManager.h"

namespace HARMONY
{
	namespace COREPLUGIN
	{
		RegisterModuleClass(HMBoostAsio)
		HPROTOCOL HMBoostAsio::CreateTCPClient(const char* serverIP, int port, AsyncReceiveDataCallBackBinary callbackfunc)
		{
			HPROTOCOL pro = getNextHandle();
			m_protocols[pro] = CreateObject<NETWORK::AsioTCPIPClient>();
			m_protocols[pro]->RegisterAsyncReceiveCallBack(callbackfunc);
			static_cast<NETWORK::ITCPClient*>(m_protocols[pro])->Connect(serverIP, port);
			return pro;
		}

		void HMBoostAsio::SendData(HPROTOCOL handle, HMArray<uint8_t>& data)
		{
			m_protocols[handle]->AsyncSend(data);
		}

		void HMBoostAsio::Terminate()
		{
			for (auto& protcl : m_protocols)
			{
				protcl.second->Terminate();
			}
		}

		HPROTOCOL HMBoostAsio::getNextHandle()
		{
			return ++m_nextHandle;
		}

	}
}