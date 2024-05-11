#pragma once

class CORE_API GameManager
{
public:
	static bool Init();
	static void Run();
	static void Stop();
	static void Terminate();
private:
	static inline bool _isRunning = true;
};