#define GC_THREADS
#include"AsioTCPIPClient.h"
#include"LogManager/LogManager.h"
#include"GameLoopManager/GameLoopManager.h"
#include"gc/gc.h"
#include"gc_cpp.h"

namespace HARMONY
{
	namespace NETWORK
	{
		//TODO: メンバにするとバグるので修正が必要
		asio::io_context io_context;
		AsioTCPIPClient::AsioTCPIPClient():
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
						OutputDebugString(std::to_wstring(bytes_transferred).c_str());
						AsyncSendMainData(data);
					}
					else {
						auto err = ec.message();
						HM_ERROR_LOG("red", TSTR("データの送信に失敗"));
					}
				});
		}

		void AsioTCPIPClient::AsyncSendMainData(const HMArray<uint8_t>& data)
		{
			auto sharedData = std::make_shared<HMArray<uint8_t>>(data);
			asio::async_write(socket, asio::buffer(sharedData->GetData(), sharedData->GetSize()),
				[this](const asio::error_code& ec, std::size_t bytes_transferred) {
					if (!ec) {
						OutputDebugString(std::to_wstring(bytes_transferred).c_str());
					}
					else {
						HM_ERROR_LOG("red", TSTR("データの送信に失敗"));
					}
				});
		}

		void AsioTCPIPClient::AsyncReceiveHeader()
		{
			auto header = std::make_shared<DataHeader>();
			asio::async_read(socket, asio::buffer(header.get(), sizeof(DataHeader)),
				[this, header](const asio::error_code& ec, std::size_t datasize) {
					if (!ec) {
						if (datasize == sizeof(size_t))
						{
							// ヘッダ受信成功。データ本体の受信を開始
							AsyncReceiveData(*header);
						}
					}
					else {
						HM_ERROR_LOG("red", TSTR("ヘッダの取得に失敗"));
						if (ec.value() == 2)
						{
							EventManager::GetEvent<>(TSTR("Disconnection")).Broadcast();
						}
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
						AsyncReceiveHeader();
					}
					else {
						HM_ERROR_LOG("red", TSTR("データ本体の取得に失敗"));
						if (ec.value() == 2)
						{
							EventManager::GetEvent<>(TSTR("Disconnection")).Broadcast();
						}
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

		void AsioTCPIPClient::RegisterDisConnectCallBack(std::function<void()> func)
		{
			_disConnectCallBack = func;
		}

		void AsioTCPIPClient::Running()
		{
			GC_stack_base sb;
			GC_get_stack_base(&sb);
			GC_register_my_thread(&sb);  // スレッドを登録

			io_context.run();  // io_contextの実行

			GC_unregister_my_thread();  // スレッドの登録解除
		}

		void AsioTCPIPClient::connect_handler(const asio::error_code& ec)
		{
			if (!ec) {
				_netthred = std::thread(std::bind(&AsioTCPIPClient::Running, this));
			}
			else {
				HM_ERROR_LOG("red", TSTR("接続に失敗"));
			}
		}
	}
}