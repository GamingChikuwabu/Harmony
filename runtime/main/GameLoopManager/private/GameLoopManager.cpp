#include"EventManager.h"
#include "GameLoopManager.h"

namespace HARMONY
{
	void GameLoopManager::Run()
	{
        using Clock = std::chrono::high_resolution_clock;
        auto lastTime = Clock::now();
        float deltaTime = 0.0f;
        

       
        HARMONY::EventManager::GetEvent<>(TEXT("OnReady")).Broadcast();
        while (running) {
            auto currentTime = Clock::now();
            deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
            lastTime = currentTime;
            // イベントを発火
            HARMONY::EventManager::GetEvent<>(TEXT("OnUpdate")).Broadcast(); 
            HARMONY::EventManager::GetEvent<>(TEXT("OnRender")).Broadcast(); 
            frameCount++;
            totalTime += deltaTime;
            // シンプルなフレームレート計算
            if (totalTime >= 1.0f) {
                fps = frameCount / totalTime;
                printf("%d\n", frameCount);
                frameCount = 0;
                totalTime = 0.0f;
            }
            frameindex++;
        }
	}

	void GameLoopManager::Stop()
	{
        running = false;
	}

    void GameLoopManager::AssertLoop(const std::string& message, const char* file, int line)
    {
        running = false;
    }

	float GameLoopManager::GetFPS()
	{
        return fps;
	}

	float GameLoopManager::GetDeltaTime()
	{
        return deltaTime;
	}
    int GameLoopManager::GetNowFrameIndex()
    {
        uint32_t index = frameindex % 2;
        printf("%d",index);
        return index;
    }
}