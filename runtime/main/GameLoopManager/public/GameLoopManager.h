#pragma once
#include <chrono>
#pragma warning(disable:4251)

namespace HARMONY
{
	class GAMELOOPMANAGER_API GameLoopManager
	{
	public:
		static void Run();
		static void Stop(); 
		static void AssertLoop(const std::string& message, const char* file, int line);
		static float GetFPS();
		static float GetDeltaTime();
		static int GetNowFrameIndex();
	private:
		static inline float deltaTime = 0.0f;
		static inline bool running = true;
		static inline float fps = 0.0f;
		static inline float totalTime = 0.0f;
		static inline int frameCount = 0;
		static inline unsigned long long frameindex = 1; 
	};
}