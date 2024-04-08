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

#include"ModuleManager.h"
#include"EventManager.h"
#include<functional>
#include"ModuleManager/IModule.h"
#include"Utility.hpp"

namespace HARMONY
{
	namespace EDITOR
	{
		// コマンド情報を格納する構造体
		struct CommandInfo {
			int id;
			std::string description;
		};

		HMCLASS()
		struct MyStruct
		{
			HM_CLASS_BODY()

		};

		struct DataHeader
		{
			size_t dataSize;
			unsigned int command;
		};
		class HMMODIPCMANAGER_API HMModIPCManager : public IModule 
		{
		public:
			HMModIPCManager();
			~HMModIPCManager();
			bool AwakeInitialize()override;
			bool LateInitialize()override;
			void RegisterCallBack(int command, std::function<void(const std::vector<char>& data)> func);
			void SendIPCData4Editor(unsigned int command, std::vector<char>& data);
			CommandInfo GetCommandInfo(const char* commandname);
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
				EventManager::GetEvent<int, std::vector<char>&>("SendData").Broadcast(_hProtocol, buffer);

				// 送信されたバイト数が合計サイズと一致するか確認
				return true;
			}
		private:
			void Tarminate(const std::vector<char>& data);
			void debugLog(const char* log);
			void getDataCallBack(const std::vector<char>& data);
			void LoadCommands(const HMString& filename);
			int									_hProtocol;
			std::unordered_map<int, std::vector<std::function<void(const std::vector<char>& data)>>> _callBackFuncArray;
			std::unordered_map<std::string, CommandInfo> commandMap;
		};
	}
}