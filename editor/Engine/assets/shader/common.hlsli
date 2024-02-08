struct VertexIn
{
    float3 pos : POSITION; // ���_�ʒu
    float2 uv : TEXCOORD; // UV���W
    float3 normal : NORMAL; // �@��
};

struct VertexOut
{
    float4 pos : SV_POSITION; // ���_�ʒu
    float2 uv : TEXCOORD; // UV���W
    float3 worldPos : WORLDPOS; // ���E���W
    float3 normal : NORMAL; // �@��
};

cbuffer MatrixBuffer : register(b0)
{
    matrix World; // ���[���h�s��
    matrix View; // �r���[�s��
    matrix Projection; // �v���W�F�N�V�����s��
}

cbuffer LightBuffer : register(b1)
{
    float3 lightDirection; // ���C�g�̕���
    float3 lightColor; // ���C�g�̐F
    float lightIntensity; // ���C�g�̋��x
}

cbuffer CameraBuffer : register(b2)
{
    float3 cameraPosition; // �J�����̈ʒu
}