#pragma once

#include"ModuleManager.h"
#include"IWindow.h"

namespace HARMONY
{
	namespace CORE
	{
		class HMModWindow : public IModule
		{
		public:
			HMModWindow();
			~HMModWindow();
			bool AwakeInitialize()override;
			void* GetMainWindowHandle() { return _mainWindowHandle; }
		private:
			IWindow* _nativeWindow;
			void* _mainWindowHandle;
		};
	}
}