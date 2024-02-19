#include"HMObject.h"
#include"main.h"
#include<filesystem>
#include<typeinfo>
#include<iostream>
#include<memory>
#include"TypeManager.h"
#include"variant.h"

//#ifdef 0
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR argv, int argc)
//#else
int main(int argc, char** argv)
//#endif // _WIN32
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	// メモリリークを検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _WIN32
	using namespace HARMONY;
	std::shared_ptr<int> a = std::make_shared<int>();
	variant var = a;
	if (var.GetType().IsWrapped())
	{
		if (var.GetType() == type::Get<std::shared_ptr<int>>())
		{
			if (type::Get<int>() == var.GetWrappedType())
			{
				printf("same");
			}
		}
		std::unique_ptr<int> t = std::move(var.Convert<std::unique_ptr<int>>());
	}
	ModuleManager::CommandLineAnalyze(argc, (void**)argv);
	LogManager::InitLogManager();
	EventManager::GetEvent<const char*, const char*, int>("Assert").Add(GameLoopManager::AssertLoop);
	if (!ModuleManager::Initialize())
	{
		LogManager::WriteToFile(std::filesystem::path(ModuleManager::GetProjectAssetsPath()).append("Logs").string());
		return -1;
	}
	HM_DEBUG_LOG("white","成功");
	GameLoopManager::Run();
	ModuleManager::Terminate();
	LogManager::WriteToFile(std::filesystem::path(ModuleManager::GetProjectAssetsPath()).append("Logs").string());
	return 0;
}