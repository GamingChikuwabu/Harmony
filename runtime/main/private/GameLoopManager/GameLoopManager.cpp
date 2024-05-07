#include "EventManager/EventManager.h"
#include "GameLoopManager/GameLoopManager.h"
#include"LogManager.h"

namespace HARMONY
{
	void GameLoopManager::Run()
	{
        using Clock = std::chrono::high_resolution_clock;
        auto lastTime = Clock::now();
        float deltaTime = 0.0f;

        HARMONY::EventManager::GetEvent<>(TSTR("OnReady")).Broadcast();
        while (running) {
            auto currentTime = Clock::now();
            //ミリ秒
            deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
            lastTime = currentTime;
            // イベントを発火

            //Windowsのメッセージ処理
            EventManager::GetEvent<>(TSTR("OnWindowUpdate")).Broadcast();
            //入力処理の更新
            EventManager::GetEvent<>(TSTR("OnInputUpdate")).Broadcast();
            //各種更新処理
            EventManager::GetEvent<float>(TSTR("OnPreUpdate")).Broadcast(deltaTime);
            //アニメーションの更新
            EventManager::GetEvent<float>(TSTR("OnAnimationUpdate")).Broadcast(deltaTime);
            //スクリプトの更新
            EventManager::GetEvent<float>(TSTR("OnBehaviorUpdate")).Broadcast(deltaTime);
            //AIの更新
            EventManager::GetEvent<float>(TSTR("OnAIUpdate")).Broadcast(deltaTime);
            //物理演算の更新
            EventManager::GetEvent<float>(TSTR("OnPhysicsUpdate")).Broadcast(deltaTime);
            //遅延更新処理
            EventManager::GetEvent<float>(TSTR("OnLateBehaviorUpdate")).Broadcast(deltaTime);
            //描画更新処理
            EventManager::GetEvent<float>(TSTR("OnRenderUpdate")).Broadcast(deltaTime);
            //描画処理
            EventManager::GetEvent<>(TSTR("OnRender")).Broadcast();
            //フレーム終了処理
            EventManager::GetEvent<>(TSTR("OnFrameFinalized")).Broadcast();

            frameCount++;
            totalTime += deltaTime;
            // シンプルなフレームレート計算
            if (totalTime >= 1.0f) {
                fps = frameCount / totalTime;
                HM_DEBUG_LOG("white", TSTR("FPS:%f"), fps)
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