#pragma once
#include<DirectXMath.h>

class ITexture2D;
class IShaderObject;
class ICommandBuffer;

namespace HARMONY
{
	namespace MATH
	{
		class Float3;
	}
}
/// @brief マテリアルのインターフェース
class IMaterial
{
public:
	virtual ~IMaterial() = default;
	virtual void SetVertexShader(IShaderObject* shader) = 0;
	virtual void SetGeometryShader(IShaderObject* shader) = 0;
	virtual void SetHallShader(IShaderObject* shader) = 0;
	virtual void SetDomainShader(IShaderObject* shader) = 0;
	virtual void SetTessellationShader(IShaderObject* shader) = 0;
	virtual void SetPixelShader(IShaderObject* shader) = 0;
	virtual IShaderObject* GetVertexShader() = 0;
	virtual IShaderObject* GetGeometryShader() = 0;
	virtual IShaderObject* GetHallShader() = 0;
	virtual IShaderObject* GetDomainShader() = 0;
	virtual IShaderObject* GetTessellationShader() = 0;
	virtual IShaderObject* GetPixelShader() = 0;
	virtual void BindMaterial(ICommandBuffer* cmd) = 0;
	virtual void BindTexture(ICommandBuffer* cmd, ITexture2D* texture) = 0;

};

using namespace HARMONY::MATH;

/// @brief ベーシックマテリアル

struct alignas (256) BasicMaterial
{
	bool		_isUseAlbedoTexture;	// テクスチャを使用するかどうか
	Float3		_albedo;				//アルベド
	bool		_isUseMetallicRoughness;//メタリックとラフネスを使用するかどうか
	float		_metallic;				//金属度
	float		_roughness;				//粗さ
	bool		_isUseNormalMap;		// ノーマルマップを使用するかどうか
	float		_normalMapIntensity;	// ノーマルマップの強度
};