#include"Core/Engine/Time.h"
#include<chrono>

bool Time::Init()
{
	auto nowTime = std::chrono::high_resolution_clock::now();
	_lastTime = std::chrono::duration_cast<std::chrono::microseconds>(nowTime).count();;
	_worldTime = 0.0f;
	_deltaTime = 0.0f;
	return true;
}

void Time::Update()
{
	auto currentTime = std::chrono::high_resolution_clock::now();


	std::chrono::duration<float> delta = currentTime.count() - _lastTime;
	_deltaTime = delta.count() / 1000000.0f; // マイクロ秒から秒に変換
	_worldTime += _deltaTime;
	_lastTime = currentTime;

}

double Time::GetDeltaTime()
{
	return 0.0f;
}

double Time::GetWorldTime()
{
	return 0.0f;
}

double Time::GetFPS()
{
	return 0.0f;
}