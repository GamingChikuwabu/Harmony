#include"HMDirectX12DescriptorPool.h"


namespace HARMONY 
{
	namespace PLATFORM
	{
		namespace WINDOWS
        {
            bool HMDirectX12DescriptorPool::CreateDescriptorPool(ID3D12Device* _device, uint32_t numCBV_SRV_UAV, uint32_t numRTV, uint32_t numDSV, uint32_t numSampler)
            {
                HRESULT hr;

                // CBV_SRV_UAVのディスクリプタヒープを作成する
                D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
                heapDesc.NumDescriptors = numCBV_SRV_UAV;
                heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
                heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

                hr = _device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_c_s_u_heap));
                if (FAILED(hr))
                {
                    return false;
                }

                for (uint32_t i = 0; i < numCBV_SRV_UAV; i++)
                {
                    m_CVB_SRV_UAV_Queue.push(i);
                }

                // RTVのディスクリプタヒープを作成する
                heapDesc.NumDescriptors = numRTV;
                heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
                heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE; // RTVはシェーダー可視ではない

                hr = _device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_rtv_heap));
                if (FAILED(hr))
                {
                    return false;
                }

                for (uint32_t i = 0; i < numRTV; i++)
                {
                    m_RTV_Queue.push(i);
                }

                // DSVのディスクリプタヒープを作成する
                heapDesc.NumDescriptors = numDSV;
                heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
                heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE; // DSVはシェーダー可視ではない

                hr = _device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_dsv_heap));
                if (FAILED(hr))
                {
                    return false;
                }

                for (uint32_t i = 0; i < numDSV; i++)
                {
                    m_DSV_Queue.push(i);
                }

                // Samplerのディスクリプタヒープを作成する
                heapDesc.NumDescriptors = numSampler;
                heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
                heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

                hr = _device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_sampler_heap));
                if (FAILED(hr))
                {
                    return false;
                }

                for (uint32_t i = 0; i < numSampler; i++)
                {
                    m_Sampler_Queue.push(i);
                }
                m_device = _device;
                return true;
            }

            void HMDirectX12DescriptorPool::CreatePoolObject(D3D12_DESCRIPTOR_HEAP_TYPE type, std::shared_ptr<PoolObject>& poolObj)
            {

                switch (type)
                {
                case D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV:
                    poolObj = std::make_shared<PoolObject>(&m_CVB_SRV_UAV_Queue);
                    poolObj->m_heapNumber = m_CVB_SRV_UAV_Queue.front(); // ディスクリプタヒープ内のインデックスを取得
                    m_CVB_SRV_UAV_Queue.pop(); // キューからインデックスを削除

                    // CPUディスクリプタハンドルの計算
                    poolObj->m_handleCPU = m_c_s_u_heap->GetCPUDescriptorHandleForHeapStart();
                    poolObj->m_handleCPU.ptr += static_cast<SIZE_T>(poolObj->m_heapNumber) * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

                    // GPUディスクリプタハンドルの計算
                    poolObj->m_handleGPU = m_c_s_u_heap->GetGPUDescriptorHandleForHeapStart();
                    poolObj->m_handleGPU.ptr += static_cast<SIZE_T>(poolObj->m_heapNumber) * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

                    break;
                case D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER:
                    // Samplerの処理
                    poolObj = std::make_shared<PoolObject>(&m_Sampler_Queue);
                    poolObj->m_heapNumber = m_Sampler_Queue.front();
                    m_Sampler_Queue.pop();

                    poolObj->m_handleCPU = m_sampler_heap->GetCPUDescriptorHandleForHeapStart();
                    poolObj->m_handleCPU.ptr += static_cast<SIZE_T>(poolObj->m_heapNumber) * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);

                    // サンプラーヒープは通常GPUからのみアクセスされるため、GPUハンドルのみを設定
                    poolObj->m_handleGPU = m_sampler_heap->GetGPUDescriptorHandleForHeapStart();
                    poolObj->m_handleGPU.ptr += static_cast<SIZE_T>(poolObj->m_heapNumber) * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
                    break;

                case D3D12_DESCRIPTOR_HEAP_TYPE_RTV:
                    // RTVの処理
                    poolObj = std::make_shared<PoolObject>(&m_RTV_Queue);
                    poolObj->m_heapNumber = m_RTV_Queue.front();
                    m_RTV_Queue.pop();

                    poolObj->m_handleCPU = m_rtv_heap->GetCPUDescriptorHandleForHeapStart();
                    poolObj->m_handleCPU.ptr += static_cast<SIZE_T>(poolObj->m_heapNumber) * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
                    break;

                case D3D12_DESCRIPTOR_HEAP_TYPE_DSV:
                    // DSVの処理
                    poolObj = std::make_shared<PoolObject>(&m_DSV_Queue);
                    poolObj->m_heapNumber = m_DSV_Queue.front();
                    m_DSV_Queue.pop();

                    poolObj->m_handleCPU = m_dsv_heap->GetCPUDescriptorHandleForHeapStart();
                    poolObj->m_handleCPU.ptr += static_cast<SIZE_T>(poolObj->m_heapNumber) * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
                    break;
                default:
                    break;
                }

            }

            void HMDirectX12DescriptorPool::Terminate()
            {
                m_c_s_u_heap.Reset();
                m_dsv_heap.Reset();
                m_rtv_heap.Reset();
                m_sampler_heap.Reset();
            }
		}
	}
}
