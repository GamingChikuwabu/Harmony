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
				void SetTexture(ITexture2D* texture, int index) override;
			private:
				ComPtr<ID3D12PipelineState> _pipelineState;
				ComPtr<ID3D12RootSignature> _rootSignature;
				HARMONY::HMArray<ITexture2D*> _textures;
				IShaderObject* _vertexShader;
				IShaderObject* _GeometryShader;
				IShaderObject* _hallShader;
				IShaderObject* _domainShader;
				IShaderObject* _tessellationShader;
				IShaderObject* _pixelShader;
			};
		}
	}
}