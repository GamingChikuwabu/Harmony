struct VertexIn
{
    float3 pos : POSITION; // 頂点位置
    float2 uv : TEXCOORD; // UV座標
    float3 normal : NORMAL; // 法線
};

struct VertexOut
{
    float4 pos : SV_POSITION; // 頂点位置
    float2 uv : TEXCOORD; // UV座標
    float3 worldPos : WORLDPOS; // 世界座標
    float3 normal : NORMAL; // 法線
};

cbuffer MatrixBuffer : register(b0)
{
    matrix World; // ワールド行列
    matrix View; // ビュー行列
    matrix Projection; // プロジェクション行列
}

cbuffer LightBuffer : register(b1)
{
    float3 lightDirection; // ライトの方向
    float3 lightColor; // ライトの色
    float lightIntensity; // ライトの強度
}

cbuffer CameraBuffer : register(b2)
{
    float3 cameraPosition; // カメラの位置
}