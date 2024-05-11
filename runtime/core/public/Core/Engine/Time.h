#pragma once

class CORE_API Time
{
public:
	/// @brief 初期化
	/// @return 結果
	static bool Init();
	/// @brief 更新
	static void Update();
	/// @brief デルタタイムを取得
	/// @return デルタタイム
	static double GetDeltaTime();
	/// @brief ゲーム開始からの経過時間を取得
	static double GetWorldTime();
	/// @brief fpsを取得
	static double GetFPS();
private:
	static inline double _deltaTime;
	static inline double _worldTime;
	static inline double _lastTime;
};