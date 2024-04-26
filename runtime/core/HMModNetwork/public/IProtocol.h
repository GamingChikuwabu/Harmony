#pragma once
#include<vector>
#include<functional>
#include"HMArray.h"

using AsyncReceiveDataCallBackBinary = std::function<void(const HARMONY::HMArray<uint8_t>& data)>;
using DisconnectionCallBack = std::function<void()>;
namespace HARMONY
{
	struct DataHeader
	{
		uint64_t size;//送られてくるデータのサイズ
	};
	//プロトコルのインターフェース
	class IProtocol{
	public:
		virtual ~IProtocol() {}
		virtual void Running() = 0;
		/// @brief 非同期でデータを受け取る用のコールバック関数を登録する関数
			/// @param callback コールバック関数
		virtual void RegisterAsyncReceiveCallBack(::AsyncReceiveDataCallBackBinary callback) = 0;

		/// @brief 同期的にデータを送信する関数
		/// @param data 送るバイトデータ
		virtual void AsyncSend(const HMArray<uint8_t>& data) = 0;

		/// @brief 同期的にデータを送信する関数
			/// @param data 送るバイトデータ
		virtual void Send(const HMArray<uint8_t>& data) = 0;

		/// @brief 終了処理
		virtual void Terminate() = 0;
	};
}