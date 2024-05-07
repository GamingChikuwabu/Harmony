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
				bool Initialize(void* windowHandle, uint32_t bufferWidth, uint32_t bufferHeight)override;
				void Present()override;
				void Terminate()override;
				uint32_t GetSwapBufferSizeW()override;
				uint32_t GetSwapBufferSizeH()override;
				void Resize(uint32_t width, uint32_t height)override;
				void SetFullScreen(bool enable)override;
				void SetVSync(bool enable)override;
				void SetRenderTarget(float r,float g,float b)override;
			private:
				//=====================================================================
				// メンバ関数
				//=====================================================================
				bool CreateRenderTarget();
				void ResetRenderTarget();
				bool CreateDsv();
				void ResetDsv();
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