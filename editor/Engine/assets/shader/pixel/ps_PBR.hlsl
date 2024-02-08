#include"../common.hlsli"
// アルベド、粗さ、金属度をテクスチャとして定義
Texture2D albedoTexture : register(t0); // アルベドテクスチャ
Texture2D roughnessTexture : register(t1); // 粗さテクスチャ
Texture2D metallicTexture : register(t2); // 金属度テクスチャ
Texture2D normalTexture : register(t3); // 法線テクスチャ

SamplerState textureSampler : register(s0); // テクスチャサンプラー

struct PixelIn {
    float4 pos : SV_POSITION; // 頂点位置
    float2 uv : TEXCOORD;     // UV座標
    float3 worldPos : WORLDPOS; // 世界座標
    float3 normal : NORMAL;   // 法線
};

struct PixelOut {
    float4 color : SV_TARGET; // 出力色
};

PixelOut psmain(PixelIn pin) {
    PixelOut pout;

    // テクスチャからマテリアルプロパティをサンプリング
    float3 albedo = albedoTexture.Sample(textureSampler, pin.uv).rgb;
    float roughness = roughnessTexture.Sample(textureSampler, pin.uv).r;
    float metallic = metallicTexture.Sample(textureSampler, pin.uv).r;
    float3 normalMap = normalTexture.Sample(textureSampler, pin.uv).rgb;
    
    // 法線マップを正規化し、[-1, 1] の範囲に変換
    float3 normal = normalize(normalMap * 2.0f - 1.0f);

    // ライトとカメラの方向の計算
    float3 lightDir = normalize(-lightDirection);
    float3 viewDir = normalize(cameraPosition - pin.worldPos);

    // ハーフランバート拡散反射の計算
    float ndotl = max(dot(normal, lightDir), 0.0);
    float diffuseTerm = 0.5 * ndotl + 0.5; // ハーフランバート
    float3 diffuseLight = diffuseTerm * lightColor * lightIntensity;

    float3 halfDir = normalize(lightDir + viewDir);
    float ndoth = max(dot(normal, halfDir), 0.0);
    float vdoth = max(dot(viewDir, halfDir), 0.0);

    // フレネル項（Schlickの近似）
    float3 F0 = float3(0.04, 0.04, 0.04); // 非金属の場合
    F0 = lerp(F0, albedo, metallic); // 金属の場合
    float3 F = F0 + (1.0 - F0) * pow(1.0 - vdoth, 5.0);

    // 幾何項
    float k = (roughness + 1.0) * (roughness + 1.0) / 8.0;
    float geo = ndotl / (ndotl * (1.0 - k) + k);

    // 分布項（GGX/Trowbridge-Reitz）
    float d = roughness * roughness;
    float denom = ndoth * ndoth * (d - 1.0) + 1.0;
    float D = d / (3.14 * denom * denom);

    // スペキュラ反射の計算
    float3 specular = diffuseLight * F * geo * D / (4.0 * ndotl);

    // 環境光、拡散反射、スペキュラ反射の計算
    float3 ambient = 0.03 * albedo;
    float3 diffuse = albedo * diffuseLight;

    // 色の計算
    pout.color = float4(ambient + diffuse + specular, 1.0);

    return pout;
}