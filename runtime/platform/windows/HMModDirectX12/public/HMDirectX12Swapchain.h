#pragma once
#include"ISwapchain.h"
#include<wrl/client.h>
#include<d3d12.h>
#include<dxgi1_6.h>
using Microsoft::WRL::ComPtr;

namespace HARMONY
{
	namespace PLATFORM 
	{
		namespace WINDOWS
		{
			class HMDirectX12SwapChain : public ISwapchain
			{
			public:
				HMDirectX12SwapChain();
				~HMDirectX12SwapChain();
				bool Initialize(void* windowHandle, unsigned int bufferWidth, unsigned int bufferHeight);
				void Present();
				void Terminate();
				unsigned int GetSwapBufferSizeW();
				unsigned int GetSwapBufferSizeH();
				void Resize(unsigned int width, unsigned int height);
				void SetVSync(bool enable);
				void SetRenderTarget(float r,float g,float b);

			private:
				//=====================================================================
				// メンバ関数
				//=====================================================================
				bool CreateRenderTarget();
				bool CreateDsv();
				bool CreateCommandLists();

				//=====================================================================
				// メンバ変数
				//=====================================================================
				static const int backbuffernum = 2;
				ComPtr<IDXGISwapChain4> m_swapchain;//スワップチェイン

				ComPtr<ID3D12DescriptorHeap> rtvHeap;//レンダーターゲットのディスクリプタ
				std::vector< ComPtr<ID3D12Resource>>backBuffer;//バックバッファ

				ComPtr<ID3D12DescriptorHeap> dsvHeap;// 深度ステンシルビューのディスクリプタ
				ComPtr<ID3D12Resource> depthStencilBuffer;// 深度バッファリソース

				// マルチスレッドレンダリング用のコマンドアロケータとコマンドリスト
				std::vector<ComPtr<ID3D12CommandAllocator>> m_commandAllocators;
				std::vector<ComPtr<ID3D12GraphicsCommandList>> m_commandLists;

				ID3D12Device*		_device;
				ID3D12CommandQueue* _queue;
				uint32_t m_width;
				uint32_t m_height;
				uint32_t m_frameCount;
				bool _isFullScreen;
				bool _vsyncEnabled;
			};
		}
	}
}