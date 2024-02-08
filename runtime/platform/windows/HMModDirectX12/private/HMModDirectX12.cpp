#include"HMModDirectX12.h"
#include"ModuleManager.h"
#include"HMDirectX12Swapchain.h"
#include"HMDirectX12ShaderObject.h"
#include"HMDirectX12Material.h"

//必要なライブラリファイルのロード
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"user32.lib") 
#pragma comment(lib,"Gdi32.lib") 
#pragma comment(lib,"Ole32.lib") 
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"winmm.lib") 

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			//モジュールを登録する
			RegisterModuleClass(HMModDirectX12);
			HMModDirectX12::HMModDirectX12()
				:_fenceEvent(nullptr)
				,_fenceValue(0)
			{}
			HMModDirectX12::~HMModDirectX12()
			{
			}
			bool HMModDirectX12::AwakeInitialize()
			{
#if defined(_DEBUG)	
				ID3D12Debug* debugController;
				if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
				{
					debugController->EnableDebugLayer();
				}
#endif
				//DX12デバイス作成
				{
					auto hr = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(_device.GetAddressOf()));
					if (FAILED(hr))
					{
						return false;
					}
				}
#ifdef _DEBUG
				ComPtr<ID3D12DebugDevice> debugDevice;
				if (SUCCEEDED(_device.As(&debugDevice)))
				{
					debugDevice->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
				}
#endif
				//コマンドキュー作成
				{
					D3D12_COMMAND_QUEUE_DESC queueDesc = {};
					queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
					queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
					_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(_commandQueue.GetAddressOf()));
				}

				//フェンス作成
				{
					_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(_fence.GetAddressOf()));
					_fenceValue = 1;
					_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
					if (_fenceEvent == nullptr)
					{
						return false;
					}
				}


				m_descriptorPool = std::make_shared<HMDirectX12DescriptorPool>();
				m_descriptorPool->CreateDescriptorPool(_device.Get(), 512, 128, 4, 1);
				return true;
			}

			void HMModDirectX12::Terminate()
			{
				WiteGPU();
				// イベントハンドルの解放
				if (_fenceEvent)
				{
					CloseHandle(_fenceEvent);
					_fenceEvent = nullptr; // セーフティのため、nullptrに設定
				}
				_fence.Reset();
				_commandQueue.Reset();
				_device.Reset();
			}

			std::shared_ptr<void> HMModDirectX12::CreateResource(ResourceType type)
			{
				std::shared_ptr<void> resource;
				switch (type)
				{
				case ResourceType::SwapChain:
					resource = std::make_shared<HMDirectX12SwapChain>();
					break;
				case ResourceType::CommandBuffer:
					break;
				case ResourceType::RenderTarget:
					break;
				case ResourceType::ShaderObject:
					resource = std::make_shared<HMDirectX12ShaderObject>();
					break;
				case ResourceType::Material:
					resource = std::make_shared<HMDirectX12Material>();
					break;
				default:
					break;
				}
				return resource;
			}

			void HMModDirectX12::WiteGPU()
			{
				// コマンドキューにシグナルを送信
				auto hr = _commandQueue->Signal(_fence.Get(), _fenceValue); 
				if (FAILED(hr)) 
				{
					// エラー処理
				}

				// フェンスが完了するのを待つ
				if (_fence->GetCompletedValue() < _fenceValue) 
				{
					hr = _fence->SetEventOnCompletion(_fenceValue, _fenceEvent); 
					if (FAILED(hr)) 
					{
						// エラー処理
					}
					WaitForSingleObject(_fenceEvent, INFINITE); 
				}

				// フェンス値をインクリメント
				_fenceValue++;
			}
		}
	}
}