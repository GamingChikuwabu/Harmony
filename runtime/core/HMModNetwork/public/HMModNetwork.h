#pragma once
#include<functional>
#include"IProtocol.h"
#include"INetWorkModule.h"

namespace HARMONY
{
	namespace CORE
	{
		//ネットワークモジュールを管理するモジュール
		class HMModNetwork : public IModule
		{
		public:
			HMModNetwork();
			~HMModNetwork();
			bool AwakeInitialize()override;
			void Terminate()override;
		private:
			void CreateTCPClient(const char* serverIP, int port, AsyncReceiveDataCallBackBinary callbackfunc,HPROTOCOL& protocolID);
			void SendData(HPROTOCOL handle, HMArray<uint8_t>& data);
			INetWorkModule* m_pNetworkMod;
		};
	}
}