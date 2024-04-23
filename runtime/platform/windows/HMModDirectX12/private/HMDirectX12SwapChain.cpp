#include"HMDirectX12Swapchain.h"
#include"ModuleManager.h"
#include"IRenderingAPI.h"
#include"HMModDirectX12.h"
#include"d3dx12.h"

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			HMDirectX12SwapChain::HMDirectX12SwapChain()
			{
			}
			HMDirectX12SwapChain::~HMDirectX12SwapChain()
			{
			}
			bool HMDirectX12SwapChain::Initialize(void* windowHandle, unsigned int bufferWidth, unsigned int bufferHeight)
			{
				IRenderingAPI* renderapi = ModuleManager::GetModule<IRenderingAPI>();
				HMModDirectX12* directX12obj = dynamic_cast<HMModDirectX12*>(renderapi); 
				_device = directX12obj->GetDevice();
				_queue = directX12obj->GetCommandQueue();

				m_width = bufferWidth;
				m_height = bufferHeight;
				
				//スワップチェーン作成
				{
					DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
					swapChainDesc.BufferCount = backbuffernum;
					swapChainDesc.Width = bufferWidth;
					swapChainDesc.Height = bufferHeight;
					swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
					swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
					swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
					swapChainDesc.SampleDesc.Count = 1;
					ComPtr<IDXGIFactory4> factory;
					CreateDXGIFactory1(IID_PPV_ARGS(&factory));
					auto hr = factory->CreateSwapChainForHwnd(_queue, (HWND)windowHandle, &swapChainDesc, NULL, NULL, (IDXGISwapChain1**)m_swapchain.GetAddressOf());
					if (FAILED(hr))
					{
						return false;
					}
				}

				if (!CreateRenderTarget())
				{
					return false;
				}

				if (!CreateDsv())
				{
					return false;
				}

				if (!CreateCommandLists())
				{
					return false;
				}
				return true;
			}

			void HMDirectX12SwapChain::Present()
			{
				// 現在のバックバッファインデックスを取得
				UINT backBufferIndex = m_swapchain->GetCurrentBackBufferIndex(); 
				// コマンドリストを実行
				ID3D12CommandList* ppCommandLists[] = { m_commandLists[backBufferIndex].Get() }; 
				// バックバッファのリソースバリアを設定（レンダーターゲットからプレゼントへ）
				CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
					backBuffer[backBufferIndex].Get(),
					D3D12_RESOURCE_STATE_RENDER_TARGET,
					D3D12_RESOURCE_STATE_PRESENT);

				// コマンドリストを再度リセットしてバリアを記録
				m_commandLists[backBufferIndex]->Reset(m_commandAllocators[backBufferIndex].Get(), nullptr);
				m_commandLists[backBufferIndex]->ResourceBarrier(1, &barrier);
				m_commandLists[backBufferIndex]->Close();

				_queue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
				m_swapchain->Present(0, 0);
			}

			void HMDirectX12SwapChain::Terminate()
			{

			}

			unsigned int HMDirectX12SwapChain::GetSwapBufferSizeW()
			{
				return m_width;
			}
			unsigned int HMDirectX12SwapChain::GetSwapBufferSizeH()
			{
				return m_height;
			}
			void HMDirectX12SwapChain::Resize(unsigned int width, unsigned int height)
			{
			}
			void HMDirectX12SwapChain::SetVSync(bool enable)
			{
			}

			void HMDirectX12SwapChain::SetRenderTarget(float r, float g, float b)
			{
				// 現在のバックバッファインデックスを取得
				UINT backBufferIndex = m_swapchain->GetCurrentBackBufferIndex(); 

				// 対応するコマンドアロケータをリセット
				m_commandAllocators[backBufferIndex]->Reset(); 

				// コマンドリストをリセットし、コマンドアロケータを使用する
				m_commandLists[backBufferIndex]->Reset(m_commandAllocators[backBufferIndex].Get(), nullptr); 

				// バックバッファのリソースバリアを設定（プレゼントからレンダーターゲットへ）
				CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition( 
					backBuffer[backBufferIndex].Get(), 
					D3D12_RESOURCE_STATE_PRESENT, 
					D3D12_RESOURCE_STATE_RENDER_TARGET); 
				m_commandLists[backBufferIndex]->ResourceBarrier(1, &barrier); 

				// レンダーターゲットビューと深度ステンシルビューのハンドルを取得
				CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart(), backBufferIndex, 
					_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)); 
				CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(dsvHeap->GetCPUDescriptorHandleForHeapStart()); 

				// レンダーターゲットと深度ステンシルビューをセット
				m_commandLists[backBufferIndex]->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

				// バックバッファをクリア
				const float clearColor[] = { r, g, b, 1.0f }; 
				m_commandLists[backBufferIndex]->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr); 
				m_commandLists[backBufferIndex]->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr); 

				// コマンドリストをクローズ（これによりコマンドが記録される）
				m_commandLists[backBufferIndex]->Close(); 

				// コマンドリストを実行
				ID3D12CommandList* ppCommandLists[] = { m_commandLists[backBufferIndex].Get() };
				_queue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
			}
			
			bool HMDirectX12SwapChain::CreateRenderTarget()
			{
				//レンダーターゲットの作成
				{
					// ディスクリプタヒープの作成
					D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
					rtvHeapDesc.NumDescriptors = backbuffernum; // バッファの数に対応
					rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
					rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
					_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

					// バックバッファとレンダーターゲットビューの作成
					SIZE_T rtvDescriptorSize = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
					CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());

					backBuffer.resize(backbuffernum);

					for (UINT i = 0; i < backbuffernum; ++i) // バッファの数だけ繰り返す
					{
						m_swapchain->GetBuffer(i, IID_PPV_ARGS(&backBuffer[i]));

						// レンダーターゲットビューの作成
						_device->CreateRenderTargetView(backBuffer[i].Get(), nullptr, rtvHandle);

						// 次のディスクリプタの位置へ
						rtvHandle.Offset(1, rtvDescriptorSize);
					}

				}
				return true;
			}

			bool HMDirectX12SwapChain::CreateDsv()
			{
				// 深度バッファのリソース記述子を作成
				D3D12_RESOURCE_DESC depthStencilDesc; 
				depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D; 
				depthStencilDesc.Alignment = 0; 
				depthStencilDesc.Width = m_width;
				depthStencilDesc.Height = m_height;
				depthStencilDesc.DepthOrArraySize = 1; 
				depthStencilDesc.MipLevels = 1; 
				depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // 一般的な深度フォーマット 
				depthStencilDesc.SampleDesc.Count = 1; 
				depthStencilDesc.SampleDesc.Quality = 0; 
				depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN; 
				depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; 

				// 深度バッファのクリア値を設定
				D3D12_CLEAR_VALUE depthOptimizedClearValue; 
				depthOptimizedClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; 
				depthOptimizedClearValue.DepthStencil.Depth = 1.0f; 
				depthOptimizedClearValue.DepthStencil.Stencil = 0; 

				auto prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
				_device->CreateCommittedResource( 
					&(prop),
					D3D12_HEAP_FLAG_NONE,
					&depthStencilDesc,
					D3D12_RESOURCE_STATE_DEPTH_WRITE,
					&depthOptimizedClearValue,
					IID_PPV_ARGS(&depthStencilBuffer));

				// 深度ステンシルビューのディスクリプタヒープを作成
				D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
				dsvHeapDesc.NumDescriptors = 1;
				dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
				dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
				_device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

				// 深度ステンシルビューの作成
				_device->CreateDepthStencilView(depthStencilBuffer.Get(), nullptr, dsvHeap->GetCPUDescriptorHandleForHeapStart());
				return true;
			}

			bool HMDirectX12SwapChain::CreateCommandLists()
			{
				//コマンドリストの作成
				{
					m_commandAllocators.resize(backbuffernum);
					m_commandLists.resize(backbuffernum);
					for (size_t i = 0; i < backbuffernum; i++)
					{
						auto hr = _device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocators[i]));
						if (FAILED(hr))
						{
							return false;
						}
						hr = _device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocators[i].Get(), NULL, IID_PPV_ARGS(&m_commandLists[i]));
						if (FAILED(hr))
						{
							return false;
						}
						m_commandLists[i]->Close();
					}
				}
				return true;
			}
		}
	}
}
