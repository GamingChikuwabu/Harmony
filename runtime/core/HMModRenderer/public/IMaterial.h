#pragma once
#include<string_view>
#include<map>
#include<IShaderObject.h>


/// @brief マテリアルのインターフェース
class IMaterial
{
public:
	virtual ~IMaterial() = default;
protected:
	IShaderObject* _vertexshader;
	IShaderObject* _pixelShader;
};