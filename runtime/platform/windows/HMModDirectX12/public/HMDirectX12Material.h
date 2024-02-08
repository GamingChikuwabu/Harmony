#pragma once
#include"IMaterial.h"
#include"d3dx12.h"
#include<wrl/client.h>
#include<d3dcompiler.h>

using Microsoft::WRL::ComPtr;

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			class HMDirectX12Material : IMaterial
			{
			public:
				HMDirectX12Material();
				~HMDirectX12Material();
				bool InitMaterial();
			private:
				ComPtr<ID3D12PipelineState> _pipelineState;
				ComPtr<ID3D12RootSignature> _rootSignature;
			};
		}
	}
}