#include"main.h"


#ifdef _WIN32
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
	GC_INIT()
	// スレッドの登録を許可
	GC_allow_register_threads();

	EventManager::GetEvent<>(TEXT("Init")).Broadcast();
	EventManager::GetEvent<>(TEXT("Ready")).Broadcast();
	EventManager::GetEvent<>(TEXT("Terminate")).Broadcast();

	GC_gcollect();
	GC_dump();
	return 0;
}