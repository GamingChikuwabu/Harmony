#pragma once
#include<vector>
#include<functional>
#include"IModule.h"

namespace HARMONY
{
	//サーバーやクライアントの通信にアクセスするためのハンドル
	using HPROTOCOL = int;
	using DataReceivedCallback = std::function<void(const std::vector<char>& data)>;
	class INetWorkModule : public IModule
	{
		HM_CLASS_BODY(IModule)
	public:
		virtual HPROTOCOL CreateTCPClient(const char* serverIP, int port, DataReceivedCallback callbackfunc) = 0;
		virtual void SendData(HPROTOCOL handle, std::vector<char>& data) = 0;
		virtual void StartReceive(HPROTOCOL handle) = 0;
	};
}