#include"Core/Engine/Time.h"
#include<chrono>
using Clock = std::chrono::high_resolution_clock;

bool Time::Init()
{
	auto temp = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> duration = temp.time_since_epoch();
	_lastTime = duration.count();
	_worldTime = 0.0f;
	_deltaTime = 0.0f;
	return true;
}

void Time::Update()
{
	auto currentTime = std::chrono::system_clock::now();
	auto temp = std::chrono::duration<float, std::milli>(currentTime.time_since_epoch());
	float nowTime = temp.count();
	_deltaTime = nowTime - _lastTime; // マイクロ秒から秒に変換
	_worldTime += _deltaTime;
	_lastTime = nowTime;
	_fpscounter++;
}

float Time::GetDeltaTime()
{
	return _deltaTime;
}

float Time::GetWorldTime()
{
	return _worldTime;
}

float Time::GetFPS()
{
	auto fps = _fpscounter / _fpstimer;
	_fpscounter = 0;
	_fpstimer = 0.0f;
	return fps;
}

uint64_t Time::GetWorldFrame()
{
	return _worldFrame;
}