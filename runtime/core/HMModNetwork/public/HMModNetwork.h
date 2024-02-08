#pragma once
#include"ModuleManager.h"
#include"HMJson.h"
#include<functional>
#include"IProtocol.h"
#include"INetWorkModule.h"

namespace HARMONY
{
	namespace CORE
	{
		//サーバーやクライアントの通信にアクセスするためのハンドル
		using HPROTOCOL = int;
		//コールバック関数
		using DataReceivedCallback = std::function<void(const std::vector<char>& data)>;

		//ネットワークモジュールを管理するモジュール
		class HMModNetwork : public IModule
		{
		public:
			HMModNetwork();
			~HMModNetwork();
			bool AwakeInitialize()override;
			void Terminate()override;
		private:
			void CreateTCPClient(const char* serverIP, int port, DataReceivedCallback callbackfunc,HPROTOCOL& protocolID);
			void SendData(HPROTOCOL handle, std::vector<char>& data);
			INetWorkModule* m_pNetworkMod;
		};
	}
}