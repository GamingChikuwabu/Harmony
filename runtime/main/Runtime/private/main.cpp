#define GC_DEBUG 
#include"Utility.hpp"
#include"Refrection.hpp"
#include"main.h"
#include<typeinfo>
#include<iostream>
#include<memory>
#include<vector>

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
	obj._array.push_back(2);


	Property* p = (PropertyArray*)GC_malloc(sizeof(PropertyArray));
	new (p) PropertyArray(TEXT("test"), &HMObject::_array);

	if (p->GetKind() == PropertyKind::Array)
	{
		PropertyArray* str = dynamic_cast<PropertyArray*>(p);
		ScriptArray sarray = str->GetScriptArray(&obj);
		size_t size = sarray.GetSize();
		void* ptr = sarray.GetData();
		int* intaa = reinterpret_cast<int*>(ptr);
		printf("%d", intaa[0]);
	}

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