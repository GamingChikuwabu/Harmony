#pragma once
#include<inttypes.h>

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
	static float GetDeltaTime();
	/// @brief ゲーム開始からの経過時間を取得
	static float GetWorldTime();
	/// @brief 前回呼び出した時からの平均FPSを取得
	static float GetFPS();
	/// @brief ゲームが始まってからのフレーム数を取得
	/// @return フレーム数
	static uint64_t GetWorldFrame();
private:
	static inline float _deltaTime;
	static inline float _worldTime;
	static inline float _lastTime;
	static inline float _fpstimer;
	static inline uint64_t _worldFrame;
	static inline uint32_t _fpscounter;
};