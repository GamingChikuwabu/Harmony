#pragma once

/// @brief コマンドバッファ用のインターフェース
class ICommandBuffer 
{
public:
	virtual ~ICommandBuffer() = default;
	virtual void SetRenderTarget() = 0;
	virtual void ClearRenderTarget() = 0;
	virtual void SetViewport() = 0;
	virtual void SetScissorRect() = 0;
	virtual void SetPipelineState() = 0;
	virtual void SetRootSignature() = 0;
	virtual void SetDescriptorHeaps() = 0;
	virtual void SetGraphicsRootSignature() = 0;

};