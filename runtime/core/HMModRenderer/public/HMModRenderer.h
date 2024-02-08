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
			IRenderingAPI* GetRenderingAPI() { return _renderapi; }
		private:
			void OnRender();
			IRenderingAPI* _renderapi;
			std::shared_ptr<ISwapchain> _swapchain;
		};
	}
}