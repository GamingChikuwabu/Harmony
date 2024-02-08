#pragma once
#include<wrl/client.h>
#include<d3dcompiler.h>
#include<d3d12.h>
#include"IIndexBuffer.h"

using Microsoft::WRL::ComPtr;

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			class HMDirectX12IndexBuffer : public IIndexBuffer
			{
			public:
				HMDirectX12IndexBuffer();
				~HMDirectX12IndexBuffer();
				bool Initialize(std::vector<uint32_t>& index)override;
			private:
				ComPtr<ID3D12Resource> m_pBuffer = nullptr; // バッファ
				D3D12_INDEX_BUFFER_VIEW m_View = {}; // インデックスバッファビュー
			};
		}
	}
}