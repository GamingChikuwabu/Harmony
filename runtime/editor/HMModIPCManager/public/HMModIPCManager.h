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
			HM_MANUAL_REGISTER_BASE_CLASS_BODY(CommandInfo)
			CommandInfo(int32_t command, HMString description) :_id(command),_description(description) 
			{}
			CommandInfo():_id(0),_description(TSTR("")) {};
			int32_t _id;
			HMString _description;
		};

		struct NetworkCommandMap
		{
			HM_MANUAL_REGISTER_BASE_CLASS_BODY(NetworkCommandMap)
			HMUnorderedMap<HMString, CommandInfo> commandMap;
		};

		struct DataHeader
		{
			size_t dataSize;
			unsigned int command;
		};

		using IPCCallBackFunc = std::function<void(const TCHAR*)>;//jsonの文字列が格納されている

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
			void RegisterCallBack(int command, IPCCallBackFunc func);
			void SendIPCData4Editor(uint32_t command, HMArray<uint8_t>& data);
			CommandInfo GetCommandInfo(const TCHAR* commandname);
			void Terminate()override;
		private:
			void disconnect();
			void getDataCallBack(const HMArray<uint8_t>& data);
		private:
			uint32_t											_hProtocol;
			HMUnorderedMap<uint32_t, HMArray<IPCCallBackFunc>>	_callBackFuncArray;
			NetworkCommandMap									_command;
		};
	}
}