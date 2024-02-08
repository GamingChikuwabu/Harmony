#pragma once
#include<memory>
#include<vector>

class ISwapchain
{
public:
	ISwapchain() {};
	virtual ~ISwapchain() {};
	virtual bool Initialize(void* windowHandle, unsigned int bufferWidth, unsigned int bufferHeight) = 0;
	virtual void Present() = 0;
	virtual void Terminate() = 0;
	virtual unsigned int GetSwapBufferSizeW() = 0;
	virtual unsigned int GetSwapBufferSizeH() = 0;
	virtual void SetRenderTarget(float r, float g, float b) = 0;
	virtual void Resize(unsigned int width, unsigned int height) = 0;
	virtual void SetVSync(bool enable) = 0;
};