#pragma once
#include"asio.hpp"
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
			virtual bool Connect(const char* Ipadder, int32_t port);

			/// @brief 非同期処理でサーバーとのコネクションを試みる関数
			/// @param Ipadder サーバーのIPアドレス
			/// @param port サーバーのポート番号
			/// @return 結果
			virtual bool AsyncConnect(const char* Ipadder, int32_t port);

			/// @brief 同期的にデータを送信する関数
			/// @param data 送るバイトデータ
			virtual void Send(const HMArray<int8_t>& data);

			/// @brief 同期的にデータを送信する関数
			/// @param data 送るバイトデータ
			virtual void AsyncSend(const HMArray<int8_t>& data);

			/// @brief 非同期でデータを受け取る用のコールバック関数を登録する関数
			/// @param callback コールバック関数
			virtual void ReceiveCallBack(AsyncReceiveDataCallBackBinary callback);

			/// @brief 非同期でデータを受け取る用のコールバック関数を登録する関数の文字列バージョン
			/// @param callback 登録するコールバック関数
			virtual void ReceiveCallBack(AsyncReceiveDataCallBackStr callback);

			/// @brief 同期的にデータを待つ関数
			/// @return 送られてきたデータ
			virtual std::vector<int8_t> SyncReceive();

			/// @brief 終了処理
			virtual void Terminate();
		private:
			asio::io_context io_context;
			tcp::socket socket;
			std::vector<char> sendData; 
			std::vector<char> data_; 
			std::thread _netthred;
			asio::ip::tcp::resolver resolver;
			asio::ip::tcp::resolver::results_type endpoints;
		private:
			// サーバからのメッセージを非同期に読み取るためのハンドラ
			void read_handler(const asio::error_code& ec, std::size_t bytes_transferred);

			// サーバへのメッセージを非同期に書き込むためのハンドラ
			void write_handler(const asio::error_code& ec, std::size_t bytes_transferred);

			// 非同期接続のハンドラ
			void connect_handler(const asio::error_code& ec);
		};
	}
}