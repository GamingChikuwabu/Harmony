#include"AsioTCPIPClient.h"
#include"LogManager/LogManager.h"

namespace HARMONY
{
	namespace NETWORK
	{
		AsioTCPIPClient::AsioTCPIPClient():
		io_context(),
		resolver(io_context),
		socket(io_context,tcp::endpoint(tcp::v4(),11111))
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
				AsyncReceiveHeader();
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

		void AsioTCPIPClient::Send(const HMArray<uint8_t>& data)
		{
			std::size_t datasize = data.GetSize();
			DataHeader header{ datasize };
			asio::write(socket, asio::buffer(&datasize, sizeof(DataHeader)));
			asio::write(socket, asio::buffer(data.GetData(), datasize));
		}

		void AsioTCPIPClient::AsyncSend(const HMArray<uint8_t>& data)
		{
			auto header = std::make_shared<DataHeader>();
			std::size_t datasize = data.GetSize();
			header->size = datasize;
			asio::async_write(socket, asio::buffer(header.get(), sizeof(DataHeader)),
				[this, header, data](const asio::error_code& ec, std::size_t bytes_transferred) {
					if (!ec) {
						AsyncSendMainData(data);
					}
					else {
						HM_DEBUG_LOG("red", TSTR("データの送信に失敗"));
					}
				});
		}

		void AsioTCPIPClient::AsyncSendMainData(const HMArray<uint8_t>& data)
		{
			auto sharedData = std::make_shared<HMArray<uint8_t>>(data);
			asio::async_write(socket, asio::buffer(sharedData->GetData(), sharedData->GetSize()),
				[this](const asio::error_code& ec, std::size_t bytes_transferred) {
					if (!ec) {
						
					}
					else {
						HM_DEBUG_LOG("red", TSTR("データの送信に失敗"));
					}
				});
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
						HM_DEBUG_LOG("red", TSTR("ヘッダの取得に失敗"));
					}
				});
		}

		void AsioTCPIPClient::AsyncReceiveData(DataHeader mainDataInfo)
		{
			auto data = std::make_shared<HMArray<uint8_t>>(mainDataInfo.size);
			asio::async_read(socket, asio::buffer(data->GetData(), mainDataInfo.size),
				[this, data,mainDataInfo](const asio::error_code& ec, std::size_t /*bytes_transferred*/) {
					if (!ec) {
						_callBackFunc(*data);
					}
					else {
						HM_DEBUG_LOG("red", TSTR("データ本体の取得に失敗"));
					}
				});
		}

		void AsioTCPIPClient::RegisterAsyncReceiveCallBack(AsyncReceiveDataCallBackBinary callback)
		{
			_callBackFunc = callback;
		}

		HMArray<uint8_t> AsioTCPIPClient::SyncReceive()
		{
			return HMArray<uint8_t>();
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