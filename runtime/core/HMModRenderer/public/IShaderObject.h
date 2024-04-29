#pragma once
#include<vector>
#include<unordered_map>
#include<string>
#include<typeindex>

class IShaderObject 
{
public:
	virtual ~IShaderObject() = default;
	virtual void InitShaderObject(const char* path) = 0;
	virtual void Terminate() = 0;
	virtual uint32_t TextureCount() = 0;
	virtual uint32_t SamplerCount() = 0;
	virtual uint32_t ConstantBufferCount() = 0;
};