#include"../common.hlsli"

VertexOut vsmain(VertexIn vin)
{
    VertexOut vout;

    // ワールド座標を計算
    float4 worldPosition = mul(float4(vin.pos, 1.0), World);

    // ワールド、ビュー、プロジェクション行列を組み合わせて頂点位置を変換
    matrix wvp = mul(mul(World, View), Projection);
    vout.pos = mul(worldPosition, wvp);

    // UV座標と法線をそのまま出力
    vout.uv = vin.uv;
    vout.normal = mul(vin.normal, (float3x3) World); // 法線をワールド行列で変換
    vout.worldPos = worldPosition.xyz;

    return vout;
}