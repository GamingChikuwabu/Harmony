#include "HMModIPCManager.h"
#include"EventManager.h"
#include"INetWorkModule.h"
#include"LogManager.h"
#include<fstream>
#include"HMJson.h"
#include<functional>

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
			LoadCommands(std::filesystem::path(ModuleManager::GetEnginePath()).append("config").append("networkcommandlist.json").string());
			EventManager::GetEvent<const char*, int, DataReceivedCallback, HPROTOCOL&>
				("CreateTCPClient")
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
			this->RegisterCallBack(this->GetCommandInfo("ShutdownRuntime").id,std::bind(&HMModIPCManager::Tarminate, this, std::placeholders::_1));
			return true;
		}

		void HMModIPCManager::RegisterCallBack(int command, std::function<void(const std::vector<char>& data)> func)
		{
			_callBackFuncArray[command].push_back(func);
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
			EventManager::GetEvent<HPROTOCOL, std::vector<char>&>("SendData").Broadcast(_hProtocol, combinedData);
		}

		CommandInfo HMModIPCManager::GetCommandInfo(const char* commandname)
		{
			return commandMap[commandname];
		}

		void HMModIPCManager::debugLog(const char* log)
		{
			// 文字列をstd::vector<char>に変換 
			std::vector<char> logData(log, log + strlen(log));
			// イベントをブロードキャスト
			EventManager::GetEvent<HPROTOCOL, std::vector<char>&>("SendData").Broadcast(_hProtocol, logData);
		}

		void HMModIPCManager::getDataCallBack(const std::vector<char>& data)
		{
			size_t offset = 0;
			while (offset < data.size()) {
				if (offset + sizeof(DataHeader) > data.size()) {
					HM_DEBUG_LOG("red", "受信データが不足しています。");
					break; // ヘッダを読むための十分なデータがない
				}

				// ヘッダの抽出
				DataHeader header;
				std::memcpy(&header, &data[offset], sizeof(header));
				offset += sizeof(header);

				if (offset + header.dataSize > data.size()) {
					HM_DEBUG_LOG("red", "データサイズが不一致です。");
					break; // データサイズが不一致
				}

				// コマンドに対応するコールバック関数を呼び出す
				auto callbacks = _callBackFuncArray.find(header.command);
				if (callbacks != _callBackFuncArray.end()) {
					for (auto& callback : callbacks->second) {
						// 適切なデータ部分を抽出してコールバックに渡す
						std::vector<char> dataBlock(data.begin() + offset, data.begin() + offset + header.dataSize);
						callback(dataBlock);
					}
				}

				offset += header.dataSize; // データサイズ分だけオフセットを進める
			}
		}
		void HMModIPCManager::LoadCommands(const HMString& filename)
		{



			rapidjson::Document doc = LoadJson(filename.c_str());
			const rapidjson::Value& commands = doc["commands"];
			for (auto& command : commands.GetArray()) {
				CommandInfo info;
				info.id = command["id"].GetInt();
				info.description = command["description"].GetString();
				commandMap[command["name"].GetString()] = info;
			}
		}

		void HMModIPCManager::Tarminate(const std::vector<char>& data)
		{
			HM_ASSERT(false,"終了")
		}
	}
}