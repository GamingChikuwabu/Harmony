#pragma once
#include<memory>
#include<vector>

class ISwapchain
{
public:
	ISwapchain() {};
	virtual ~ISwapchain() {};
	virtual bool Initialize(void* windowHandle, uint32_t bufferWidth, uint32_t bufferHeight) = 0;
	virtual void Present() = 0;
	virtual void Terminate() = 0;
	virtual uint32_t GetSwapBufferSizeW() = 0;
	virtual uint32_t GetSwapBufferSizeH() = 0;
	virtual void SetRenderTarget(float r, float g, float b) = 0;
	virtual void Resize(uint32_t width, uint32_t height) = 0;
	virtual void SetVSync(bool enable) = 0;
	virtual void SetFullScreen(bool enable)=0;
};