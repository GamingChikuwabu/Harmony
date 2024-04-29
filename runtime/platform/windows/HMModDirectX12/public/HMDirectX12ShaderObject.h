#pragma once
#include"IShaderObject.h"
#include<d3d12.h>
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
			class HMDirectX12ShaderObject : public IShaderObject
			{
			public:
				HMDirectX12ShaderObject();
				~HMDirectX12ShaderObject();
				void InitShaderObject(const char* path)override;
				void Terminate()override;
			private:
				void RefConstantBuffer(ComPtr<ID3D12ShaderReflection> refl);
				void RefTexture(ComPtr<ID3D12ShaderReflection> refl);
				void RefSampler(ComPtr<ID3D12ShaderReflection> refl);
				void InitRootParameter();
				ComPtr<ID3DBlob> m_shaderObject;
				std::vector<CD3DX12_ROOT_PARAMETER> rootParams;
				std::unordered_map<int, std::unordered_map<std::string, std::string>> m_ConstantBuffers;
				std::unordered_map<int, std::string> m_Textures;
				std::unordered_map<int, std::string> m_Samplers;
			};
		}
	}
}