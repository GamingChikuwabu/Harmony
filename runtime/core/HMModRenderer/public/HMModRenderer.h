#pragma once
#include"ModuleManager.h"
#include"IRenderingAPI.h"
#include"ISwapchain.h"

namespace HARMONY
{
	namespace CORE
	{
		class HMModRenderer : public IModule
		{
		public:
			HMModRenderer();
			~HMModRenderer();
			bool AwakeInitialize()override;
			bool Initialize()override;
			void Terminate()override;
			IRenderingAPI* GetRenderingAPI() { return _renderapi; }
		private:
			void OnRender();
			IRenderingAPI* _renderapi;
			ISwapchain* _swapchain;
		};
	}
} /// namespace HARMONY