#include"HMObject.h"
namespace HARMONY
{
	template<typename Archive>
	void archive(Archive& ar, HMObject& obj)
	{
		ar& make_nvp("_guid", obj._guid);
	};
}
#include"main.h"
#include<filesystem>
#include<typeinfo>
#include<iostream>
#include"Archive/JsonOArchive.h"
#include"TypeManager.h"

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
	TypeManager::Init();
	//テストコード
	int a = 0;
	int c;
	int* pA = &a;
	float fa;
	HMObject object;
	{
		std::ofstream ofs("text.json");
		JsonOArchive archive(ofs);
		archive & MAKE_NVP(a);
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