#pragma once

#include<wrl/client.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<IRenderterget.h>
#include"HMDirectX12DescriptorPool.h"
using Microsoft::WRL::ComPtr;

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			class HMDirectX12RenderTerget : public IRendertarget
			{
			public:
				HMDirectX12RenderTerget();
				~HMDirectX12RenderTerget();

			private:
				std::shared_ptr<PoolObject> object;
				ComPtr<ID3D12Resource> m_renderTarget;
			};
		}
	}
}