#include<vector>


template<class T>
class IVertexBuffer
{
public:
    IVertexBuffer() {}
    virtual ~IVertexBuffer() {}

    // バッファの初期化
    virtual bool initialize(std::vector<T>& data) = 0;

    // データをバッファに設定
    virtual void setData(const std::vector<T>& data, unsigned int usage) = 0;
};