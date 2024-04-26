#include "HMModIPCManager.h"
#include"INetWorkModule.h"
#include"IProtocol.h"
#include"INetWorkModule.h"
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
			EventManager::GetEvent<>(TSTR("Disconnection")).Add(std::bind(&HMModIPCManager::disconnect, this));
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

		void HMModIPCManager::SendIPCData4Editor(uint32_t command, HMArray<uint8_t>& data)
		{
			uint32_t _command = command;
			HMArray<uint8_t> combinedData;
			combinedData.Add(reinterpret_cast<uint8_t*>(&_command), sizeof(uint32_t));
			combinedData.Add(data.GetData(), data.GetSize());
			EventManager::GetEvent<HPROTOCOL, HMArray<uint8_t>&>(TSTR("SendData")).Broadcast(_hProtocol, combinedData);
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

		void HMModIPCManager::disconnect()
		{
			GameLoopManager::Stop();
		}

		// データを受信したときに呼び出されるコールバック関数
		void HMModIPCManager::getDataCallBack(const HMArray<uint8_t>& data)
		{
			//　コマンドのサイズ
			constexpr int32_t CommandSize = sizeof(int32_t);

			// データの先頭からコマンドを取得
			int32_t command = *reinterpret_cast<int32_t*>(data.GetData());
			// データの先頭からコマンドを取り除いた部分を取得し、文字列に変換
			const void* jsonStrv = reinterpret_cast<void*>(&data[CommandSize]);
			std::vector<char> buffer(data.GetSize(), 0);
			memcpy(buffer.data(), jsonStrv, data.GetSize());
			const TCHAR* jsonStr = reinterpret_cast<const wchar_t*>(buffer.data());
			
			// コマンドに対応するコールバック関数を取得し、呼び出す
			auto callBackFuncArray = _callBackFuncArray[command];
			for (auto func : callBackFuncArray)
			{
				func(jsonStr);
			}
		}
	}
}