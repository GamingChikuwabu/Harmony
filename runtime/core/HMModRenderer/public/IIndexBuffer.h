#pragma once
#include<vector>

class IIndexBuffer
{
public:
	IIndexBuffer() {};
	virtual ~IIndexBuffer() {};
	virtual bool Initialize(std::vector<uint32_t>& index) = 0;
};