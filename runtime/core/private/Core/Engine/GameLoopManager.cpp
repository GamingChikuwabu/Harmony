#include"Core/Engine/GameLoopManager.h"
#include"Core/Engine/EventManager.h"

bool GameManager::Init()
{
	EventManager::GetEvent<>(TSTR("Init")).Broadcast();
	return true;
}

void GameManager::Run()
{
	EventManager::GetEvent<>(TSTR("Ready")).Broadcast();
	while (_isRunning)
	{
		
		EventManager::GetEvent<>(TSTR("Ready")).Broadcast();
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