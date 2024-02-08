#pragma once
#include"EventManager.h"
#include<string>
#include <mutex>
#include <queue>
#include<unordered_map>
#pragma warning(disable:4251)

#ifdef _WIN32
#ifdef LOGMANAGER_EXPORTS
#define LOGMANAGER_API  __declspec(dllexport) 
#else
#define LOGMANAGER_API  __declspec(dllimport)
#endif // LOGMANAGER_API
#else
#define LOGMANAGER_API
#endif // WIND32


namespace HARMONY
{
#ifdef _WIN32
#include <Windows.h>
#include <string>

	inline std::string ToUtf8(const std::wstring& wstr) {
		if (wstr.empty()) return std::string();

		int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), nullptr, 0, nullptr, nullptr);
		std::string strTo(sizeNeeded, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], sizeNeeded, nullptr, nullptr);

		return strTo;
	}

	inline std::wstring FromUtf8(const std::string& str) {
		if (str.empty()) return std::wstring();

		int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), nullptr, 0);
		std::wstring wstrTo(sizeNeeded, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], sizeNeeded);

		return wstrTo;
	}

#endif // _WIN32
#if defined(_DEVELOP) || defined(_DEBUG)
#define HM_DEBUG_LOG(color,c_char, ...)\
	{\
		char moji[256];\
		snprintf(moji, sizeof(moji), c_char, ##__VA_ARGS__);\
		HARMONY::EventManager::GetEvent<const char*,const char*>("DebugLog").Broadcast(moji,color);\
	}
#else
#define HM_DEBUG_LOG(c_char, ...) //
#endif // _DEBUG


#if defined(_DEVELOP) || defined(_DEBUG)
#define HM_ENGIN_LOG(color,c_char, ...)\
	{\
		char moji[256];\
		snprintf(moji, sizeof(moji), c_char, ##__VA_ARGS__);\
		printf(c_char, ##__VA_ARGS__);\
		HARMONY::EventManager::GetEvent<const char*,const char*>("EngineLog").Broadcast(moji,color);\
	}
#else
#define HM_DEBUG_LOG(c_char, ...) //
#endif // _DEBUG

#define HM_ASSERT(o,message,...)\
	if(o == false){\
		HARMONY::EventManager::GetEvent<const char*, const char*,int>("Assert").Broadcast(message, __FILE__, __LINE__);\
	};

	struct LogMessage
	{
		std::string _message;
		std::string _color;
	};

	class LOGMANAGER_API LogManager
	{
	public:
		static void InitLogManager();
		static void WriteToFile(const std::string& filename);
		static void EnqueueLog(const std::string& log,const char* color);
		static LogMessage DequeueLog();
	private:
		static void AddLog(const char* message,const char* color);
		static void AssertLog(const char* message, const char* file, int line);// アサートメッセージを記録
		static inline std::vector<std::string> _logs; // ログを保持するコンテナ
		static inline std::queue<LogMessage> _logQueue; // ログを保持するキュー
		static inline std::mutex _mutex; // スレッドセーフな操作のためのミューテックス
	};
}// namespace HARMONY