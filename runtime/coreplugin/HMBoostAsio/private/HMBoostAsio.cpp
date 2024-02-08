#include"HMBoostAsio.h"
#include"AsioTCPIP.h"
#include"ModuleManager.h"

namespace HARMONY
{
	namespace COREPLUGIN
	{
		RegisterModuleClass(HMBoostAsio)
		HPROTOCOL HMBoostAsio::CreateTCPClient(const char* serverIP, int port, DataReceivedCallback callbackfunc)
		{
			HPROTOCOL pro = getNextHandle();
			m_protocols[pro] = std::make_unique<AsioTCPIP>();
			m_protocols[pro]->registerDataReceivedCallback(callbackfunc);
			m_protocols[pro]->connect(serverIP, port);
			StartReceive(pro);
			return pro;
		}
		void HMBoostAsio::StartReceive(HPROTOCOL handle)
		{
			m_protocols[handle]->receive();
		}
		void HMBoostAsio::SendData(HPROTOCOL handle, std::vector<char>& data)
		{
			m_protocols[handle]->send(data);
		}
		void HMBoostAsio::Terminate()
		{
			for (auto& protcl : m_protocols)
			{
				protcl.second->disconnect();
				protcl.second->stop_server();
			}
		}
	}
}