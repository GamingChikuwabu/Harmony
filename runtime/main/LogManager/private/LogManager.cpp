#include "LogManager.h"
#include <fstream>
#include <filesystem>




namespace HARMONY
{
	void LogManager::InitLogManager()
	{
		EventManager::GetEvent<const char*,const char*>("DebugLog").Add(LogManager::AddLog);
		EventManager::GetEvent<const char*, const char*,int>("Assert").Add(LogManager::AssertLog);
	}

	void LogManager::AddLog(const char* message,const char* color)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		EnqueueLog(message, color);
		_logs.push_back(message);
	}


	void LogManager::WriteToFile(const std::string& LogDir)
	{
		std::ofstream file(std::filesystem::path(LogDir).append("DebugLog.txt"), std::ios::app);
		if (!file.is_open()) {
			// ファイルが開けなかった場合のエラー処理
			return;
		}
		{
			
			std::lock_guard<std::mutex> lock(_mutex);
			for (const auto& log : _logs) {
				file << ToUtf8(FromUtf8(log)) << std::endl;
			}
			_logs.clear(); // ログをクリア
		}
	}

	void LogManager::AssertLog(const char* message, const char* file, int line)
	{
		std::string fullMessage = "Assertion failed: " + std::string(message) + ", in file " + file + ", line " + std::to_string(line);
	}

	void LogManager::EnqueueLog(const std::string& log,const char* color) {
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