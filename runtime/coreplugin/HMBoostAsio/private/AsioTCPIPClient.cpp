#include"AsioTCPIPClient.h"
#include"LogManager/LogManager.h"

namespace HARMONY
{
	namespace NETWORK
	{
		AsioTCPIPClient::AsioTCPIPClient()
		:socket(io_context)
		,resolver(io_context)
		{

		}
		AsioTCPIPClient::~AsioTCPIPClient()
		{

		}

		bool AsioTCPIPClient::Connect(const char* Ipadder, int32_t port)
		{
			endpoints = resolver.resolve(Ipadder, std::to_string(port));
			asio::connect(socket, endpoints); // Corrected for synchronous connect
			return socket.is_open();
		}

		bool AsioTCPIPClient::AsyncConnect(const char* Ipadder, int32_t port)
		{
			asio::async_connect(
				socket,
				endpoints,
				std::bind(&AsioTCPIPClient::connect_handler, this,
				std::placeholders::_1));
			return true;
		}

		void AsioTCPIPClient::Send(const HMArray<int8_t>& data)
		{
			asio::send()
		}

		void AsioTCPIPClient::AsyncSend(const HMArray<int8_t>& data)
		{

		}
		void AsioTCPIPClient::ReceiveCallBack(AsyncReceiveDataCallBackBinary callback)
		{
		}
		void AsioTCPIPClient::ReceiveCallBack(AsyncReceiveDataCallBackStr callback)
		{
		}
		std::vector<int8_t> AsioTCPIPClient::SyncReceive()
		{
			return std::vector<int8_t>();
		}
		void AsioTCPIPClient::Terminate()
		{
			if (socket.is_open()) {
				socket.close();
			}
			if (_netthred.joinable()) {
				_netthred.join();
			}
		}
		void AsioTCPIPClient::read_handler(const asio::error_code& ec, std::size_t bytes_transferred)
		{

		}
		void AsioTCPIPClient::write_handler(const asio::error_code& ec, std::size_t bytes_transferred)
		{

		}
		void AsioTCPIPClient::connect_handler(const asio::error_code& ec)
		{

		}
	}
}