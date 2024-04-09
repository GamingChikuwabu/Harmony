#pragma once
#include"INetWorkModule.h"
#include"IProtocol.h"
#include"Utility.hpp"
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
			// プロトコルオブジェクトを管理
			HMUnorderedMap<HPROTOCOL,IProtocol*> m_protocols;
			//次のユニークなハンドル
			HPROTOCOL m_nextHandle;
			// 次のユニークなハンドルを生成するためのヘルパーメソッド
			HPROTOCOL getNextHandle();
		};
	}
}