#include "HMModIPCManager.h"
#include"INetWorkModule.h"
#include"IProtocol.h"
#include<functional>
#include<filesystem>

namespace HARMONY
{
	namespace EDITOR
	{
		RegisterModuleClass(HMModIPCManager)
		HMModIPCManager::HMModIPCManager()
		{
			
		}
		HMModIPCManager::~HMModIPCManager()
		{
		}

		bool HMModIPCManager::AwakeInitialize()
		{
			Ifstream ifs(std::filesystem::path(ModuleManager::GetEnginePath()).append("config").append("IPCSetting.json").string());
			EventManager::GetEvent<const char*,int, ::AsyncReceiveDataCallBackBinary,HPROTOCOL&>
				(TSTR("CreateTCPClient"))
				.Broadcast(
					"127.0.0.1"
					, 11111
					, std::bind(&HMModIPCManager::getDataCallBack, this, std::placeholders::_1)
					, _hProtocol);
			HM_ASSERT(_hProtocol != NULL, "クライアントの取得に失敗");
			return true;
		}

		bool HMModIPCManager::LateInitialize()
		{
			this->RegisterCallBack(this->GetCommandInfo(TSTR("ShutdownRuntime")).id,std::bind(&HMModIPCManager::Terminate, this, std::placeholders::_1));
			return true;
		}

		void HMModIPCManager::RegisterCallBack(int command, std::function<void(const std::vector<char>& data)> func)
		{
			_callBackFuncArray[command].Add(func);
		}

		void HMModIPCManager::SendIPCData4Editor(unsigned int command, std::vector<char>& data)
		{
			// ヘッダーを作成
			DataHeader header{ static_cast<size_t>(data.size()), command };

			// ヘッダーのサイズを計算
			size_t headerSize = sizeof(DataHeader);

			// 新しいvectorを作成し、ヘッダーと元のデータを追加
			std::vector<char> combinedData;
			combinedData.reserve(headerSize + data.size());

			// ヘッダーのデータをvectorにコピー
			const char* headerData = reinterpret_cast<const char*>(&header);
			combinedData.insert(combinedData.end(), headerData, headerData + headerSize);

			// 元のデータをvectorにコピー
			combinedData.insert(combinedData.end(), data.begin(), data.end());

			// 更新されたデータを送信
			EventManager::GetEvent<HPROTOCOL, std::vector<char>&>(TSTR("SendData")).Broadcast(_hProtocol, combinedData);
		}

		CommandInfo HMModIPCManager::GetCommandInfo(const TCHAR* commandname)
		{
			return _command.commandMap[commandname];
		}

		void HMModIPCManager::debugLog(const char* log)
		{
			// 文字列をstd::vector<char>に変換 
			std::vector<char> logData(log, log + strlen(log));
			// イベントをブロードキャスト
			EventManager::GetEvent<HPROTOCOL, std::vector<char>&>(TSTR("SendData")).Broadcast(_hProtocol, logData);
		}

		void HMModIPCManager::getDataCallBack(const HMArray<uint8_t>& data)
		{
			constexpr int32_t CommandSize = sizeof(int32_t);

			int32_t command = *reinterpret_cast<int32_t*>(data.GetData());
			const void* jsonStrv = reinterpret_cast<void*>(&data[CommandSize]);
			
			std::vector<char> buffer(data.GetSize(), 0);
			memcpy(buffer.data(), jsonStrv, data.GetSize());
			const TCHAR* jsonStr = reinterpret_cast<const wchar_t*>(buffer.data());
			OutputDebugString(jsonStr);
			printf("");
		}

		void HMModIPCManager::LoadCommands(const HMString& filename)
		{
			/*rapidjson::Document doc = LoadJson(filename);
			const rapidjson::Value& commands = doc["commands"];
			for (auto& command : commands.GetArray()) {
				CommandInfo info;
				info.id = command["id"].GetInt();
				info.description = command["description"].GetString();
				commandMap[command["name"].GetString()] = info;
			}*/
		}

		void HMModIPCManager::Terminate(const std::vector<char>& data)
		{
			HM_ASSERT(false,"終了")
		}
	}
}