#pragma once
#ifdef _WIN32
#ifdef HMMODLEVELEDITOR_EXPORTS 
#define HMMODLEVELEDITOR_API  __declspec(dllexport) 
#else
#define HMMODLEVELEDITOR_API  __declspec(dllimport)
#endif // HMMODLEVELEDITOR_API
#else
#define HMMODLEVELEDITOR_API
#endif // WIND32

#include"ModuleManager.h"
#include"IWindow.h"

namespace HARMONY
{
	namespace EDITOR
	{
		class HMModLevelEditor : public IModule
		{
		public:
			HMModLevelEditor();
			~HMModLevelEditor();
			bool AwakeInitialize()override;
			bool Initialize()override;
			void Terminate()override;
		private:
			void handleGetLevelEditorWindowHandle(const std::vector<char>& data);
			IWindow* _window;
		};
	}
}