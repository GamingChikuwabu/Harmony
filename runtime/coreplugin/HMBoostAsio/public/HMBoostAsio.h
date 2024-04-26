#pragma once
#include"INetWorkModule.h"
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

			HPROTOCOL CreateTCPClient(const char* serverIP, int port, AsyncReceiveDataCallBackBinary callbackfunc)override;
			void SendData(HPROTOCOL handle, HMArray<uint8_t>& data)override;
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