#pragma once
#include<vector>

template<class T>
class IConstantBuffer
{
public:
    IConstantBuffer() {}
    virtual ~IConstantBuffer() {}
    // バッファの初期化
    virtual bool initialize(T data) = 0;
};