#pragma once
#include<string_view>
#include<map>
#include<IShaderObject.h>
#include<ITexture2D.h>
#include"HMArray.h"

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

};