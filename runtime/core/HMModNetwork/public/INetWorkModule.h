#pragma once
#include"IModule.h"
#include"IProtocol.h"

namespace HARMONY
{
	//サーバーやクライアントの通信にアクセスするためのハンドル
	using HPROTOCOL = uint32_t;
	class INetWorkModule : public IModule
	{
	public:
		virtual HPROTOCOL CreateTCPClient(const char* serverIP, int port, AsyncReceiveDataCallBackBinary callbackfunc) = 0;
		virtual void SendData(HPROTOCOL handle, HMArray<uint8_t>& data) = 0;
	};
}