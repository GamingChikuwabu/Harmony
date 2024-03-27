#include"main.h"

#ifdef WIN32
#ifdef UNICODE
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR argv, int argc)
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR argv, int argc)
#endif // UNICODE
#else
int main(int argc, char** argv)
#endif//WIN32
//#endif // _WIN32
{
	GC_INIT();
	// 自動GCを無効にする
	GC_disable();
	using namespace HARMONY;

	HMObject obj;
	obj._guid = TEXT("guid");
	obj._array.Add(2);

	//ModuleManager::CommandLineAnalyze(argc, (void**)argv);
	//LogManager::InitLogManager();
	////EventManager::GetEvent<const char*, const char*, int>("Assert").Add(GameLoopManager::AssertLoop);
	//if (!ModuleManager::Initialize())
	//{
	//	LogManager::WriteToFile(std::filesystem::path(ModuleManager::GetProjectAssetsPath()).append("Logs").string());
	//	return -1;
	//}
	//HM_DEBUG_LOG("white","成功");
	//GameLoopManager::Run();
	//ModuleManager::Terminate();
	//LogManager::WriteToFile(std::filesystem::path(ModuleManager::GetProjectAssetsPath()).append("Logs").string());
	// 手動でガーベージコレクションを実行
	GC_gcollect();
	GC_dump();
	return 0;
}