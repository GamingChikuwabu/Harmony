#pragma once
#include"asio.hpp"
#include <asio/ip/tcp.hpp>
#include"ITCPClient.h"

namespace HARMONY
{
	namespace NETWORK
	{
		using asio::ip::tcp;
		class AsioTCPIPClient : public ITCPClient
		{
		public:
			AsioTCPIPClient();
			~AsioTCPIPClient();
			/// @brief 同期処理でサーバーとのコネクションを試みる関数
			/// @param Ipadder サーバーのIPアドレス
			/// @param port サーバーのポート番号
			/// @return 結果
			virtual bool Connect(const char* Ipadder, int32_t port)override;

			/// @brief 非同期処理でサーバーとのコネクションを試みる関数
			/// @param Ipadder サーバーのIPアドレス
			/// @param port サーバーのポート番号
			/// @return 結果
			virtual bool AsyncConnect(const char* Ipadder, int32_t port)override;

			/// @brief 同期的にデータを送信する関数
			/// @param data 送るバイトデータ
			virtual void Send(const HMArray<uint8_t>& data)override;

			/// @brief 同期的にデータを送信する関数
			/// @param data 送るバイトデータ
			virtual void AsyncSend(const HMArray<uint8_t>& data)override;

			/// @brief 非同期でデータを受け取る用のコールバック関数を登録する関数
			/// @param callback コールバック関数
			virtual void RegisterAsyncReceiveCallBack(AsyncReceiveDataCallBackBinary callback)override;

			/// @brief 同期的にデータを待つ関数
			/// @return 送られてきたデータ
			virtual HMArray<uint8_t> SyncReceive()override;

			/// @brief 終了処理
			virtual void Terminate()override;

			/// @brief 接続が切れた時呼び出される関数を登録する関数
			/// @param func 
			void RegisterDisConnectCallBack(std::function<void()> func)override;
		private:
			void Running();
			void AsyncReceiveHeader();
			void AsyncReceiveData(DataHeader mainDataInfo);
			void AsyncSendMainData(const HMArray<uint8_t>& data);

			std::thread _netthred;

			tcp::socket socket;
			/*asio::io_context io_context;*/
			asio::ip::tcp::resolver resolver;
			asio::ip::tcp::resolver::results_type endpoints;

			AsyncReceiveDataCallBackBinary _callBackFunc;
			std::function<void()> _disConnectCallBack;
		private:
			// 非同期接続のハンドラ
			void connect_handler(const asio::error_code& ec);
		};
	}
}