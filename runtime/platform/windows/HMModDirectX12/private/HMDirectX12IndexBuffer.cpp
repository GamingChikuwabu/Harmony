#include"HMDirectX12IndexBuffer.h"
#include"ModuleManager.h"
#include"HMModDirectX12.h"
#include"IRenderingAPI.h"
#include"d3dx12.h"

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			HMDirectX12IndexBuffer::HMDirectX12IndexBuffer()
			{
			}
			HMDirectX12IndexBuffer::~HMDirectX12IndexBuffer()
			{
			}
			bool HMDirectX12IndexBuffer::Initialize(std::vector<uint32_t>& index)
			{
                auto _renderApi = ModuleManager::GetModule<IRenderingAPI>();
                if (!_renderApi)
                {
                    return false;
                }
                auto dxdevice = static_cast<HMModDirectX12*>(_renderApi);

                auto prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
                auto desc = CD3DX12_RESOURCE_DESC::Buffer(index.size() * sizeof(uint32_t));

                // リソースを生成
                auto hr = dxdevice->GetDevice()->CreateCommittedResource(
                    &prop,
                    D3D12_HEAP_FLAG_NONE,
                    &desc,
                    D3D12_RESOURCE_STATE_GENERIC_READ,
                    nullptr,
                    IID_PPV_ARGS(m_pBuffer.GetAddressOf()));

                if (FAILED(hr))
                {
                    return false;
                }

                // インデックスバッファビューの設定
                m_View.BufferLocation = m_pBuffer->GetGPUVirtualAddress();
                m_View.Format = DXGI_FORMAT_R32_UINT; // インデックスの形式
                m_View.SizeInBytes = static_cast<UINT>(index.size() * sizeof(uint32_t));

          
                // マッピングする
                void* ptr = nullptr;
                hr = m_pBuffer->Map(0, nullptr, &ptr);
                if (FAILED(hr))
                {
                    return false;
                }

                // インデックスデータをマッピング先に設定
                memcpy(ptr, index.data(), index.size() * sizeof(uint32_t));

                // マッピング解除
                m_pBuffer->Unmap(0, nullptr);

                return true;
			}
		}
	}
}