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
			asio::connect(socket, endpoints);
			if(socket.is_open())
			{
				_netthred = std::thread(std::bind(&AsioTCPIPClient::Running, this));

				return true;
			}
			return false;
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

		void AsioTCPIPClient::Send(const uint32_t id,const HMArray<uint8_t>& data)
		{
			std::size_t datasize = data.GetSize();
			DataHeader header{ id,datasize };
			asio::write(socket, asio::buffer(&datasize, sizeof(DataHeader)));
			asio::write(socket, asio::buffer(data.GetData(), datasize));
		}

		void AsioTCPIPClient::AsyncSend(const uint32_t id,const HMArray<uint8_t>& data)
		{
			std::size_t datasize = data.GetSize();
			_sendDataHeader.id = id;
			_sendDataHeader.size = datasize;
			asio::async_write(socket, asio::buffer(&_sendDataHeader, sizeof(DataHeader)),
				[this](const asio::error_code& ec, std::size_t bytes_transferred) {
					write_handler_header(ec, bytes_transferred);
				});
			_sendData = std::move(data);
		}

		void AsioTCPIPClient::ReceiveCallBack(AsyncReceiveDataCallBackBinary callback)
		{

		}

		void AsioTCPIPClient::ReceiveCallBack(AsyncReceiveDataCallBackStr callback)
		{

		}

		std::vector<uint8_t> AsioTCPIPClient::SyncReceive()
		{
			return std::vector<uint8_t>();
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

		void AsioTCPIPClient::Running()
		{
			io_context.run();
		}

		void AsioTCPIPClient::AsyncReceiveHeader()
		{
			auto header = std::make_shared<DataHeader>();
			asio::async_read(socket, asio::buffer(header.get(), sizeof(DataHeader)),
				[this, header](const asio::error_code& ec, std::size_t /*bytes_transferred*/) {
					if (!ec) {
						// ヘッダ受信成功。データ本体の受信を開始
						AsyncReceiveData(*header);
					}
					else {
						// エラーハンドリング
					}
				});
		}

		void AsioTCPIPClient::AsyncReceiveData(DataHeader mainDataInfo)
		{
			auto data = std::make_shared<std::vector<uint8_t>>(mainDataInfo.size);
			asio::async_read(socket, asio::buffer(data->data(), mainDataInfo.size),
				[this, data](const asio::error_code& ec, std::size_t /*bytes_transferred*/) {
					if (!ec) {
						
					}
					else {
						// エラーハンドリング
					}
				});
		}

		void AsioTCPIPClient::AsyncSendMainData()
		{
			asio::async_write(socket, asio::buffer(_sendData.GetData(), _sendData.GetSize()),
				[this](const asio::error_code& ec, std::size_t bytes_transferred) {
					write_handler_main_data(ec, bytes_transferred);
				});
		}

		void AsioTCPIPClient::read_handler(const asio::error_code& ec, std::size_t bytes_transferred)
		{
			if (!ec) {
				// Process the data received
			}
			else {
				// Handle the error
			}
		}

		void AsioTCPIPClient::write_handler_header(const asio::error_code& ec, std::size_t bytes_transferred)
		{
			if (!ec) {
				//ヘッダをリセット
				_sendDataHeader.id = 0;
				_sendDataHeader.size = 0;
				//送るデータの本体を送信する
				AsyncSendMainData();
			}
			else {
				// Handle the error
			}
		}

		void AsioTCPIPClient::write_handler_main_data(const asio::error_code& ec, std::size_t bytes_transferred)
		{
			if (!ec) {
				_sendData.ReSize(0);
			}
			else {
				
			}
		}

		void AsioTCPIPClient::connect_handler(const asio::error_code& ec)
		{
			if (!ec) {
				_netthred = std::thread(std::bind(&AsioTCPIPClient::Running, this));
			}
			else {
				
			}
		}
	}
}