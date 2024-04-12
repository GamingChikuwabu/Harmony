#pragma once
#include<inttypes.h>
#include<functional>
#include<vector>
#include"HMArray.h"
#include"HMString.h"
#include"IProtocol.h"

namespace HARMONY
{
	namespace NETWORK
	{
		class ITCPClient : public IProtocol
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

			/// @brief 同期的にデータを待つ関数
			/// @return 送られてきたデータ
			virtual HMArray<uint8_t> SyncReceive() = 0;
		};
	}
}