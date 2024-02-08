#pragma once
#include"IRenderingAPI.h"
#include"HMDirectX12DescriptorPool.h"
#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			class HMMODDIRECTX12_API HMModDirectX12 : public IRenderingAPI
			{
			public:
				HMModDirectX12();
				~HMModDirectX12();
				bool AwakeInitialize()override;
				void Terminate()override;
				std::shared_ptr<void> CreateResource(ResourceType type)override;
				void WiteGPU()override;
				inline ID3D12Device* GetDevice() const{ return _device.Get(); }
				inline ID3D12CommandQueue* GetCommandQueue() const { return _commandQueue.Get(); }
				inline std::shared_ptr<HMDirectX12DescriptorPool>& GetDescriptorPool() { return m_descriptorPool; }
			private:
				std::shared_ptr<HMDirectX12DescriptorPool> m_descriptorPool;
				ComPtr<ID3D12Device> _device;
				ComPtr<ID3D12CommandQueue> _commandQueue;
				ComPtr<ID3D12Fence> _fence;
				UINT64 _fenceValue;
				HANDLE _fenceEvent;
			};
		}
	}
}