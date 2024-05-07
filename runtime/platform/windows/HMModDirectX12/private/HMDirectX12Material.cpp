#include "HMDirectX12Material.h"

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			HMDirectX12Material::HMDirectX12Material()
			: _vertexShader(nullptr),
			_pixelShader(nullptr),
			_GeometryShader(nullptr),
			_tessellationShader(nullptr),
			_hallShader(nullptr),
			_domainShader(nullptr)
			{
				
			}
			HMDirectX12Material::~HMDirectX12Material()
			{
			}
			void HMDirectX12Material::SetVertexShader(IShaderObject* shader)
			{
				_vertexShader = shader;
			}
			void HMDirectX12Material::SetGeometryShader(IShaderObject* shader)
			{
				_GeometryShader = shader;
			}
			void HMDirectX12Material::SetHallShader(IShaderObject* shader)
			{
				_hallShader = shader;
			}
			void HMDirectX12Material::SetDomainShader(IShaderObject* shader)
			{
				_domainShader = shader;
			}
			void HMDirectX12Material::SetTessellationShader(IShaderObject* shader)
			{
				_tessellationShader = shader;
			}
			void HMDirectX12Material::SetPixelShader(IShaderObject* shader)
			{
				_pixelShader = shader;
			}
			IShaderObject* HMDirectX12Material::GetVertexShader()
			{
				return _vertexShader;
			}
			IShaderObject* HMDirectX12Material::GetGeometryShader()
			{
				return _pixelShader;
			}
			IShaderObject* HMDirectX12Material::GetHallShader()
			{
				return _hallShader;
			}
			IShaderObject* HMDirectX12Material::GetDomainShader()
			{
				return _domainShader;
			}
			IShaderObject* HMDirectX12Material::GetTessellationShader()
			{
				return _tessellationShader;
			}
			IShaderObject* HMDirectX12Material::GetPixelShader()
			{
				return _pixelShader;
			}
		}
	}
}