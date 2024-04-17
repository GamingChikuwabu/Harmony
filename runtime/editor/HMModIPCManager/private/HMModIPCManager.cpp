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

		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(CommandInfo)
			HM_ADD_PROPERTY_STRING(CommandInfo,_description),
			HM_ADD_PROPERTY_INT32(CommandInfo,_id)
		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(CommandInfo)

		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(NetworkCommandMap)
			HM_ADD_PROPERTY_UMAP(NetworkCommandMap, commandMap)
		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(NetworkCommandMap)


		HMModIPCManager::HMModIPCManager()
		:_hProtocol(0)
		{
			
		}

		HMModIPCManager::~HMModIPCManager()
		{

		}

		bool HMModIPCManager::AwakeInitialize()
		{
			auto CommandConfigPath = std::filesystem::path(ModuleManager::GetEnginePath()).append("config").append("IPCSetting.json").string();

			if (!std::filesystem::exists(CommandConfigPath))//ファイルの存在を確認
			{
				Ofstream ofs(CommandConfigPath);
				if (ofs)
				{
					SERIALIZER::OJsonArchiver oja;
					ofs << ( oja & _command).GetRaw();
				}
				else
				{

					return false;
				}
			}
			Ifstream ifs(std::filesystem::path(ModuleManager::GetEnginePath()).append("config").append("IPCSetting.json").string());
			SERIALIZER::IJsonArchiver ij(ifs);
			ij & _command;

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
			return true;
		}

		void HMModIPCManager::RegisterCallBack(int command, IPCCallBackFunc func)
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
			auto it = _command.commandMap.find(commandname);
			if (it != _command.commandMap.end())
			{
				return it->second;
			}
			return CommandInfo();
		}

		void HMModIPCManager::Terminate()
		{
			auto CommandConfigPath = std::filesystem::path(ModuleManager::GetEnginePath()).append("config").append("IPCSetting.json").string();
			Ofstream ofs(CommandConfigPath);
			if (ofs)
			{
				SERIALIZER::OJsonArchiver oja;
				ofs << (oja & _command).GetRaw();
			}
			else
			{
				HM_ERROR_LOG("red", TSTR("ファイルの書き込みに失敗しました"));
			}
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
			
			auto callBackFuncArray = _callBackFuncArray[command];

			for (auto func : callBackFuncArray)
			{
				func(jsonStr);
			}
		}

		
	}
}