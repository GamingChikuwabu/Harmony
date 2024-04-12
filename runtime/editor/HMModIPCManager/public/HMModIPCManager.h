#pragma once
#ifdef _WIN32
#ifdef HMMODIPCMANAGER_EXPORTS 
#define HMMODIPCMANAGER_API  __declspec(dllexport) 
#else
#define HMMODIPCMANAGER_API  __declspec(dllimport)
#endif // HMMODIPCMANAGER_API
#else
#define HMMODIPCMANAGER_API
#endif // WIND32

#include"Utility.hpp"
#include<functional>


namespace HARMONY
{
	namespace EDITOR
	{
		// コマンド情報を格納する構造体
		struct CommandInfo {
			int id;
			std::string description;
		};

		struct NetworkCommandMap
		{
			HMUnorderedMap<HMString, CommandInfo> commandMap;
		};

		struct DataHeader
		{
			size_t dataSize;
			unsigned int command;
		};

		class HMMODIPCMANAGER_API HMModIPCManager : public IModule 
		{
		public:
			/// @brief デフォルトコンストラクタ
			HMModIPCManager();
			/// @brief
			~HMModIPCManager();
			/// @brief 初期化
			/// @return 
			bool AwakeInitialize()override;
			bool LateInitialize()override;
			void RegisterCallBack(int command, std::function<void(const std::vector<char>& data)> func);
			void SendIPCData4Editor(unsigned int command, std::vector<char>& data);
			CommandInfo GetCommandInfo(const TCHAR* commandname);
			// データ送信の汎用関数
			template<typename T>
			bool SendData(unsigned int command, const T& data) {
				
				// ヘッダーを作成
				DataHeader header{ static_cast<int>(sizeof(T)), command };

				// ヘッダーとデータの合計サイズを計算
				size_t totalSize = sizeof(DataHeader) + sizeof(T);

				// バッファを用意
				std::vector<char> buffer(totalSize);

				// ヘッダーをバッファにコピー
				std::memcpy(buffer.data(), &header, sizeof(DataHeader));

				// データをバッファにコピー
				std::memcpy(buffer.data() + sizeof(DataHeader), &data, sizeof(T));

				// 更新されたデータを送信
				EventManager::GetEvent<int, std::vector<char>&>(TSTR("SendData")).Broadcast(_hProtocol, buffer);

				// 送信されたバイト数が合計サイズと一致するか確認
				return true;
			}
		private:
			void Terminate(const std::vector<char>& data);
			void debugLog(const char* log);
			void getDataCallBack(const HMArray<uint8_t>& data);
			void LoadCommands(const HMString& filename);
			uint32_t									_hProtocol;
			HMUnorderedMap<uint32_t, HMArray<std::function<void(const std::vector<char>& data)>>> _callBackFuncArray;
			NetworkCommandMap _command;
		};
	}
}