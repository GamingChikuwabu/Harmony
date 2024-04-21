#pragma once
#ifdef _WIN32
#ifdef HMMODCONSOLE_EXPORTS 
#define HMMODCONSOLE_API  __declspec(dllexport) 
#else
#define HMMODCONSOLE_API  __declspec(dllimport)
#endif // HMMODCONSOLE_API
#else
#define HMMODCONSOLE_API
#endif // WIND32

#include"ModuleManager.h"
#include"HMModIPCManager.h"
#include<functional>


namespace HARMONY
{
	namespace EDITOR
	{
		class HMModConsole : public IModule
		{
		public:
			HMModConsole();
			~HMModConsole();
			bool Initialize()override;
		private:
			void SendDebugLog(const TCHAR* log,const TCHAR* color);
			HMModIPCManager* _manager;
		};
	}
}