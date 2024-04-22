#pragma warning(disable:4251)
#pragma warning(disable:4005)
#include"main.h"

#ifdef WIN32
#include<Windows.h>
#ifdef UNICODE
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR argv, int argc)
{
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR argv, int argc)
{
#endif // UNICODE
#else
int main(int argc, char** argv)
{
#endif//WIN32
//#endif // _WIN32
	GC_INIT();
	// スレッドの登録を許可
	GC_allow_register_threads();
	// 自動GCを無効にする
	//GC_disable();
	using namespace HARMONY;
	ModuleManager::CommandLineAnalyze(argc, (void**)argv);
	LogManager::InitLogManager();
	//EventManager::GetEvent<const char*, const char*, int>("Assert").Add(GameLoopManager::AssertLoop);
	if (!ModuleManager::Initialize())
	{
		LogManager::WriteToFile(std::filesystem::path(ModuleManager::GetProjectAssetsPath()).append("Logs").c_str());
		return -1;
	}
	HM_DEBUG_LOG("white",TSTR("成功"));
	GameLoopManager::Run();
	ModuleManager::Terminate();
	//LogManager::WriteToFile(std::filesystem::path(ModuleManager::GetProjectAssetsPath()).append("Logs").c_str());
	// 手動でガーベージコレクションを実行
	GC_gcollect();
	GC_dump();
	return 0;
}