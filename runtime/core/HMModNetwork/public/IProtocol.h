#pragma once
#include<vector>
#include<functional>
#include"HMObject.h"


namespace HARMONY
{
	//コールバック関数
	using DataReceivedCallback = std::function<void(const std::vector<char>& data)>;
	//プロトコルのインターフェース
	class IProtocol : public HMObject{
	public:
		virtual ~IProtocol() {}
		// クライアントとしての動作
		virtual void connect(const char* ipad, int port) = 0;
		virtual void send(std::vector<char>& data) = 0;
		virtual std::vector<char> receive() = 0;
		virtual void disconnect() = 0;
		// サーバーとしての動作
		virtual void start_server(int port) = 0;
		virtual void stop_server() = 0;
		// コールバックの登録
		virtual void registerDataReceivedCallback(DataReceivedCallback callback) = 0;
	};
}