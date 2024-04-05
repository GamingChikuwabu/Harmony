#include "LogManager/LogManager.h"
#include <fstream>
#include <filesystem>



namespace HARMONY
{
	void LogManager::InitLogManager()
	{
		EventManager::GetEvent<const TCHAR*,const TCHAR*>(TSTR("DebugLog")).Add(LogManager::AddLog);
		EventManager::GetEvent<const TCHAR*, const TCHAR*,int32_t>(TSTR("Assert")).Add(LogManager::AssertLog);
	}

	void LogManager::AddLog(const TCHAR* message,const TCHAR* color)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		EnqueueLog(message, color);
		_logs.Add(message);
	}


	void LogManager::WriteToFile(const HMString& LogDir)
	{
		std::ofstream file(std::filesystem::path(LogDir.GetRaw()).append("DebugLog.txt"), std::ios::app);
		if (!file.is_open()) {
			// ファイルが開けなかった場合のエラー処理
			return;
		}
		{
			
		}
	}

	void LogManager::AssertLog(const TCHAR* message, const TCHAR* file, int32_t line)
	{
		/*HMString fullMessage = "Assertion failed: " + HMString(message) + ", in file " + file + ", line ";*/
	}

	void LogManager::EnqueueLog(const HMString& log,const TCHAR* color) {
		//std::lock_guard<std::mutex> lock(_mutex); // ミューテックスでスレッドセーフを保証
		LogMessage map{ log ,color};
		_logQueue.push(map);
	}

	LogMessage LogManager::DequeueLog() {
		std::lock_guard<std::mutex> lock(_mutex); // ミューテックスでスレッドセーフを保証
		if (_logQueue.empty()) {
			return LogMessage(); // キューが空の場合は空の文字列を返す
		}
		LogMessage log = _logQueue.front();
		_logQueue.pop();
		return log;
	}
}