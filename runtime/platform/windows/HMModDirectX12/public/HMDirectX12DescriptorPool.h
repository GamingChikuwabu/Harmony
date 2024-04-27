#pragma once
#include<d3d12.h>
#include<wrl/client.h>
#include<iostream>
#include<queue>

using Microsoft::WRL::ComPtr;

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			struct PoolObject
			{
				PoolObject(std::queue<int>* _QueueOuner) { m_QueueOuner = _QueueOuner; }
				~PoolObject() {  };
				D3D12_CPU_DESCRIPTOR_HANDLE m_handleCPU;
				D3D12_GPU_DESCRIPTOR_HANDLE m_handleGPU;
				uint32_t m_heapNumber;
			private:
				std::queue<int>* m_QueueOuner;
			};

			class HMDirectX12DescriptorPool
			{
			public:
				bool CreateDescriptorPool(ID3D12Device* _device, uint32_t numCBV_SRV_UAV, uint32_t numRTV, uint32_t numDSV, uint32_t numSampler);
				void CreatePoolObject(D3D12_DESCRIPTOR_HEAP_TYPE type, std::shared_ptr<PoolObject>& poolObj);
				void Terminate();
			private:
				ID3D12Device* m_device;
				std::queue<int> m_CVB_SRV_UAV_Queue;
				std::queue<int> m_RTV_Queue;
				std::queue<int> m_DSV_Queue;
				std::queue<int> m_Sampler_Queue;
				ComPtr<ID3D12DescriptorHeap> m_c_s_u_heap;
				ComPtr<ID3D12DescriptorHeap> m_rtv_heap;
				ComPtr<ID3D12DescriptorHeap> m_dsv_heap;
				ComPtr<ID3D12DescriptorHeap> m_sampler_heap;
			};
		}
	}
}