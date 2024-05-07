#pragma once
#include"IMaterial.h"
#include"d3dx12.h"
#include"Utility.hpp"
#include<wrl/client.h>
#include<d3dcompiler.h>

using Microsoft::WRL::ComPtr;

class ITexture2D;
class IShaderObject;

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
				virtual void SetVertexShader(IShaderObject* shader);
				virtual void SetGeometryShader(IShaderObject* shader);
				virtual void SetHallShader(IShaderObject* shader);
				virtual void SetDomainShader(IShaderObject* shader);
				virtual void SetTessellationShader(IShaderObject* shader);
				virtual void SetPixelShader(IShaderObject* shader);
				virtual IShaderObject* GetVertexShader();
				virtual IShaderObject* GetGeometryShader();
				virtual IShaderObject* GetHallShader();
				virtual IShaderObject* GetDomainShader();
				virtual IShaderObject* GetTessellationShader();
				virtual IShaderObject* GetPixelShader();
				virtual void BindMaterial(ICommandBuffer* cmd);
				virtual void BindTexture(ICommandBuffer* cmd, ITexture2D* texture);
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