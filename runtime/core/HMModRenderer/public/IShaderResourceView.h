#pragma once

class IShaderResourceView
{
public:
	IShaderResourceView() {};
	virtual ~IShaderResourceView() {};
	bool CreateShaderResourceView() = 0;
};