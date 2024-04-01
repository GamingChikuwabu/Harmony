#pragma once
#include"IModule.h"
#include<memory>

enum class ResourceType
{
	SwapChain,
	CommandBuffer,
	RenderTarget,
	ShaderObject,
	Material
};

class IRenderingAPI : public HARMONY::IModule
{
public:
	virtual std::shared_ptr<void> CreateResource(ResourceType type) = 0;
	virtual void WiteGPU() = 0;
};