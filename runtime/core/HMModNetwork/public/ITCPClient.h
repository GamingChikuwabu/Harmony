#pragma once
#include<inttypes.h>
#include<functional>
#include<vector>
#include"HMArray.h"
#include"HMString.h"

namespace HARMONY
{
	namespace NETWORK
	{
		struct DataHeader
		{
			uint32_t id;//データの識別id
			uint64_t size;//送られてくるデータのサイズ
		};
		using AsyncReceiveDataCallBackBinary = std::function<void(const std::vector<char>& data,const DataHeader )>;
		using AsyncReceiveDataCallBackStr = std::function<void(const TCHAR* data)>;
		class ITCPClient
		{
		public:
			virtual ~ITCPClient() {};
			/// @brief 同期処理でサーバーとのコネクションを試みる関数
			/// @param Ipadder サーバーのIPアドレス
			/// @param port サーバーのポート番号
			/// @return 結果
			virtual bool Connect(const char* Ipadder,int32_t port) = 0;

			/// @brief 非同期処理でサーバーとのコネクションを試みる関数
			/// @param Ipadder サーバーのIPアドレス
			/// @param port サーバーのポート番号
			/// @return 結果
			virtual bool AsyncConnect(const char* Ipadder, int32_t port) = 0;

			/// @brief 同期的にデータを送信する関数
			/// @param data 送るバイトデータ
			virtual void Send(const uint32_t id,const HMArray<uint8_t>& data) = 0;

			/// @brief 同期的にデータを送信する関数
			/// @param data 送るバイトデータ
			virtual void AsyncSend(const uint32_t id,const HMArray<uint8_t>& data) = 0;

			/// @brief 非同期でデータを受け取る用のコールバック関数を登録する関数
			/// @param callback コールバック関数
			virtual void ReceiveCallBack(AsyncReceiveDataCallBackBinary callback) = 0;

			/// @brief 非同期でデータを受け取る用のコールバック関数を登録する関数の文字列バージョン
			/// @param callback 登録するコールバック関数
			virtual void ReceiveCallBack(AsyncReceiveDataCallBackStr callback) = 0;

			/// @brief 同期的にデータを待つ関数
			/// @return 送られてきたデータ
			virtual std::vector<uint8_t> SyncReceive() = 0;

			/// @brief 終了処理
			virtual void Terminate() = 0;
		};
	}
}