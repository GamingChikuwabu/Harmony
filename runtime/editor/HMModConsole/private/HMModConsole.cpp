#include"HMModConsole.h"
#include"EventManager.h"
#include"HMModIPCManager.h"

namespace HARMONY
{
	namespace EDITOR
	{
		struct MessageData {
			HM_MANUAL_REGISTER_BASE_CLASS_BODY(MessageData)
			HMString message; // 文字列
			HMString color;    // 文字列の色
		};

		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(MessageData)
			HM_ADD_PROPERTY_STRING(MessageData, message),
			HM_ADD_PROPERTY_STRING(MessageData, color)
		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(MessageData)

		RegisterModuleClass(HMModConsole) 
		HMModConsole::HMModConsole()
		:_manager(nullptr)
		{
		}

		HMModConsole::~HMModConsole()
		{
		}

		bool HMModConsole::Initialize()
		{
			EventManager::GetEvent<const TCHAR*, const TCHAR*>(TSTR("DebugLog")).Add(std::bind(&HMModConsole::SendDebugLog,this, std::placeholders::_1,std::placeholders::_2));
			_manager = ModuleManager::GetModule<HMModIPCManager>();
			return true;
		}

		void HMModConsole::SendDebugLog(const TCHAR* log, const TCHAR* color)
		{
			MessageData data; 
			data.message = log;
			data.color = color;

			SERIALIZER::OJsonArchiver oja;
			auto jsonStr = (oja & data);
			HMArray<uint8_t> send_data(jsonStr.Length());

			send_data.Insert(send_data.end(), reinterpret_cast<uint8_t*>(jsonStr.GetRaw()),jsonStr.Length());
			_manager->SendIPCData4Editor(_manager->GetCommandInfo(TSTR("SendLog"))._id, send_data);
		}
	}
}