#include"HMModConsole.h"
#include"EventManager.h"
#include"HMModIPCManager.h"

namespace HARMONY
{
	namespace EDITOR
	{
		struct MessageData {
			char message[246]; // 文字列
			char color[10];    // 文字列の色
		};
		RegisterModuleClass(HMModConsole)
		HMModConsole::HMModConsole()
		{
		}
		HMModConsole::~HMModConsole()
		{
		}
		bool HMModConsole::Initialize()
		{
			EventManager::GetEvent<const char*, const char*>("DebugLog").Add(std::bind(&HMModConsole::SendDebugLog,this, std::placeholders::_1,std::placeholders::_2));
			_manager = ModuleManager::GetModule<HMModIPCManager>();
			return true;
		}

		void HMModConsole::SendDebugLog(const char* log, const char* color)
		{
			std::vector<char> send_data;
			MessageData data;

			// 文字列をMessageData構造体にコピー
			size_t message_length = std::min(std::strlen(log), sizeof(data.message) - 1);
			std::strncpy(data.message, log, message_length);
			data.message[message_length] = '\0'; // 終端文字を追加

			size_t color_length = std::min(std::strlen(color), sizeof(data.color) - 1);
			std::strncpy(data.color, color, color_length);
			data.color[color_length] = '\0'; // 終端文字を追加

			// MessageData構造体の内容をバイト列としてsend_dataベクターにコピー
			const char* dataPtr = reinterpret_cast<const char*>(&data);
			size_t dataSize = sizeof(MessageData);

			send_data.insert(send_data.end(), dataPtr, dataPtr + dataSize);

			_manager->SendIPCData4Editor(_manager->GetCommandInfo("SendLog").id, send_data);
		}
	}
}