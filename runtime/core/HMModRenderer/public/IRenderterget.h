#pragma once
#include"ITexture2D.h"
#include<vector>


class IRendertarget : public ITexture2D
{
public:
	IRendertarget(){};
	virtual	~IRendertarget() {};
private:
	float color[4];
};