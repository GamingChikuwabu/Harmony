#pragma once
#include"EventManager/EventManager.h"
#include"Utility/Array/HMArray.h"
#include<string>
#include <mutex>
#include <queue>
#include<unordered_map>
#pragma warning(disable:4251)

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
        TCHAR moji[512];\
        TSPRINTF(moji, _countof(moji), c_char, ##__VA_ARGS__);\
        HARMONY::EventManager::GetEvent<const TCHAR*,const TCHAR*>(TSTR("DebugLog")).Broadcast(moji,TSTR(color));\
    }
#else
#define HM_DEBUG_LOG(c_char, ...) //
#endif // _DEBUG

#if defined(_DEVELOP) || defined(_DEBUG)
#define HM_ERROR_LOG(color,c_char, ...)\
    {\
        TCHAR moji[512];\
        TSPRINTF(moji, _countof(moji), c_char, ##__VA_ARGS__);\
        HARMONY::EventManager::GetEvent<const TCHAR*,const TCHAR*>(TSTR("DebugLog")).Broadcast(moji,TSTR(color));\
    }
#else
#define HM_DEBUG_LOG(c_char, ...) //
#endif // _DEBUG


#if defined(_DEVELOP) || defined(_DEBUG)
#define HM_WARNIN_LOG(color,c_char, ...)\
    {\
        TCHAR moji[512];\
        TSPRINTF(moji, _countof(moji), c_char, ##__VA_ARGS__);\
        HARMONY::EventManager::GetEvent<const TCHAR*,const TCHAR*>(TSTR("DebugLog")).Broadcast(moji,TSTR(color));\
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
		HARMONY::EventManager::GetEvent<const TCHAR*, const TCHAR*,int32_t>(TSTR("Assert")).Broadcast(TSTR(message), TSTR(""),__LINE__);\
	};

	struct LogMessage
	{
		HMString _message;
		HMString _color;
	};

	class UTILITY_API LogManager
	{
	public:
		static void InitLogManager();
		static void WriteToFile(const HMString& filename);
		static void EnqueueLog(const HMString& log,const TCHAR* color);
		static LogMessage DequeueLog();
	private:
		static void AddLog(const TCHAR* message,const TCHAR* color);
		static void AssertLog(const TCHAR* message, const TCHAR* file, int line);// アサートメッセージを記録
		static inline HMArray<HMString> _logs; // ログを保持するコンテナ
		static inline std::queue<LogMessage> _logQueue; // ログを保持するキュー
		static inline std::mutex _mutex; // スレッドセーフな操作のためのミューテックス
	};
}// namespace HARMONY