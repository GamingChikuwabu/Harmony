#include"Core/Engine/GameLoopManager.h"
#include"Core/Engine/EventManager.h"
#include"Core/Engine/Time.h"

bool GameManager::Init()
{
	EventManager::GetEvent<>(TSTR("Init")).Broadcast();
	return true;
}

void GameManager::Run()
{
	EventManager::GetEvent<>(TSTR("Ready")).Broadcast();
    Time::Init();
	while (_isRunning)
	{
        Time::Update();
        float deltaTime = Time::GetDeltaTime();

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
	}
}

void GameManager::Stop()
{
	_isRunning = false;
}

void GameManager::Terminate()
{
	EventManager::GetEvent<>(TSTR("Terminate")).Broadcast();
}