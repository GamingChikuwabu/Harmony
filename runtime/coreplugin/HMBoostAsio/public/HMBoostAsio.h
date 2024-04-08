#pragma once
#include"INetWorkModule.h"
#include"IProtocol.h"
#include<vector>
#include<memory>
#include<mutex>

namespace HARMONY
{
	namespace COREPLUGIN
	{
		class HMBoostAsio : public INetWorkModule
		{
		public:
			HPROTOCOL CreateTCPClient(const char* serverIP, int port, DataReceivedCallback callbackfunc)override;
			void StartReceive(HPROTOCOL handle)override;
			void SendData(HPROTOCOL handle, std::vector<char>& data)override;
			void Terminate()override;
		private:
			std::unordered_map<HPROTOCOL, std::unique_ptr<IProtocol>> m_protocols; // プロトコルオブジェクトを管理
			HPROTOCOL m_nextHandle{ 0 }; // ユニークなハンドルを生成するためのカウンタ
			// 次のユニークなハンドルを生成するためのヘルパーメソッド
			HPROTOCOL getNextHandle() {
				return ++m_nextHandle;
			}
		};
	}
}