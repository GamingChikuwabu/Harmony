#include<vector>

namespace HARMONY
{
    namespace MATH
    {
        struct Vector3f;
        struct Vector4f;
        struct Vector2f;
    }
}

// 頂点バッファのインターフェース
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

//頂点構造体
struct BasicVertex
{
    HARMONY::MATH::Vector3f position;
    HARMONY::MATH::Vector3f normal;
    HARMONY::MATH::Vector2f texCoords;
};

struct ColorVertex
{
    HARMONY::MATH::Vector3f position;
    HARMONY::MATH::Vector4f color; // RGBA形式 
};

struct SkinnedVertex
{
    HARMONY::MATH::Vector3f position;
    HARMONY::MATH::Vector3f normal;
    HARMONY::MATH::Vector2f texCoords;
    float boneWeights[4];
    int boneIndices[4];
};

struct TangentVertex
{
    HARMONY::MATH::Vector3f position;
    HARMONY::MATH::Vector3f normal;
    HARMONY::MATH::Vector2f texCoords;
    HARMONY::MATH::Vector3f tangent;
};

struct ParticleVertex
{
    HARMONY::MATH::Vector3f position;
    HARMONY::MATH::Vector4f color; // RGBA
    float size;
};
