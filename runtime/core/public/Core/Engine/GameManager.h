#pragma once

class CORE_API GameManager
{
public:
	/// @brief ゲームの初期化処理
	/// @return 結果
	static bool Init();
	
	/// @brief ゲームのメインループ
	static void Run();

	/// @brief Game loopを停止する
	static void Stop();

	/// @brief ゲームの終了処理
	static void Terminate();

	/// @brief ゲームが実行中かどうか
	static inline bool IsPaused() { return _isPaused; }

	/// @brief ゲームを一時停止する
	static inline void Pause() { _isPaused = true; }

	/// @brief ゲームを再開する
	static inline void Resume() { _isPaused = false; }
private:
	static inline bool _isRunning = true;
	static inline bool _isPaused = false;
};