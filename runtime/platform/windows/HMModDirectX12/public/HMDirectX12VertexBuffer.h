#pragma once
#include"IVertexBuffer.h"
#include"Utility.hpp"
#include"IRenderingAPI.h"
#include"HMModDirectX12.h"
#include<d3d12.h>
#include<wrl/client.h>
#include <d3dx12.h>
using Microsoft::WRL::ComPtr;

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			template<class T>
			class HMDirectX12VertexBuffer : public IVertexBuffer<T>
			{
			public:
				HMDirectX12VertexBuffer() {};
				~HMDirectX12VertexBuffer() {};
				bool initialize(std::vector<T>& data);
			private:
				ComPtr<ID3D12Resource> m_pBuffer = nullptr; // バッファ
				D3D12_VERTEX_BUFFER_VIEW m_View = {}; // 頂点バッファビュー
				D3D12_INPUT_LAYOUT_DESC m_InputLayout = {}; // 入力レイアウト
			};

			template<class T>
			inline bool HMDirectX12VertexBuffer<T>::initialize(std::vector<T>& data)
			{
				_renderApi = ModuleManager::GetModule<IRenderingAPI>();
				if (!_renderApi)
				{
					return false;
				}
				auto dxdevice = static_cast<HMModDirectX12*>(_renderApi);

				auto prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD); // ヒーププロパティ 
				auto desc = CD3DX12_RESOURCE_DESC::Buffer(data.size() * sizeof(T)); // リソースの設定（バイトサイズで指定）

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

				// 頂点バッファビューの設定
				m_View.BufferLocation = m_pBuffer->GetGPUVirtualAddress();
				m_View.SizeInBytes = static_cast<UINT>(data.size() * sizeof(T)); // データのバイトサイズ
				m_View.StrideInBytes = static_cast<UINT>(sizeof(T));

				// マッピングする
				void* ptr = nullptr;
				hr = m_pBuffer->Map(0, nullptr, &ptr);
				if (FAILED(hr))
				{
					return false;
				}

				// 頂点データをマッピング先に設定
				memcpy(ptr, data.data(), data.size() * sizeof(T)); // dataベクターから直接コピー

				// マッピング解除
				m_pBuffer->Unmap(0, nullptr);
				return true;
			}
		}
	}
}