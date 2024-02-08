#include"HMDirectX12ShaderObject.h"
#include <fstream>
#include <vector>
#include <d3dcompiler.h>
#include <dxcapi.h>
#include<dxgi.h>
#include<sstream>
#include<iomanip>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "dxcompiler")

#define DXIL_FOURCC(ch0, ch1, ch2, ch3) \
    ((uint32_t)(uint8_t)(ch0) | ((uint32_t)(uint8_t)(ch1) << 8) | \
    ((uint32_t)(uint8_t)(ch2) << 16) | ((uint32_t)(uint8_t)(ch3) << 24 ))

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
        {
			HMDirectX12ShaderObject::HMDirectX12ShaderObject()
			{
			}
			HMDirectX12ShaderObject::~HMDirectX12ShaderObject()
			{
			}
			void HMDirectX12ShaderObject::InitShaderObject(const char* path)
			{
                // csoファイルをバイナリモードで読み込み
                std::ifstream csoFile(path, std::ios::in | std::ios::binary | std::ios::ate);

                if (csoFile.is_open())
                {
                    // ファイルサイズを取得
                    std::streampos size = csoFile.tellg();

                    // ファイルの内容を読み込むためのバッファを確保
                    std::vector<char> buffer(size);

                    csoFile.seekg(0, std::ios::beg);
                    csoFile.read(buffer.data(), size);
                    csoFile.close();

                    // バッファからシェーダーオブジェクトを作成
                    HRESULT hr = D3DCreateBlob(size, m_shaderObject.GetAddressOf());
                    if (SUCCEEDED(hr))
                    {
                        memcpy(m_shaderObject->GetBufferPointer(), buffer.data(), size);
                        // dxc api を使う.
                        ComPtr<IDxcLibrary> lib;
                        DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&lib));
                        ComPtr<IDxcBlobEncoding> binBlob{};
                        lib->CreateBlobWithEncodingOnHeapCopy(buffer.data(), buffer.size(), CP_ACP, &binBlob);
                        ComPtr<IDxcContainerReflection> refl;
                        DxcCreateInstance(CLSID_DxcContainerReflection, IID_PPV_ARGS(&refl));
                        // シェーダーバイナリデータをロードし、DXILチャンクブロック（のインデックス）を得る.
                        UINT shdIndex = 0;
                        refl->Load(binBlob.Get());
                        refl->FindFirstPartKind(DXIL_FOURCC('D', 'X', 'I', 'L'), &shdIndex);
                        // シェーダーリフレクションインターフェース取得.
                        ComPtr<ID3D12ShaderReflection> shaderReflection;
                        if (FAILED(refl->GetPartReflection(shdIndex, IID_PPV_ARGS(&shaderReflection))))
                        {
                            return;
                        }
                        RefConstantBuffer(shaderReflection);
                        RefTexture(shaderReflection);
                        RefSampler(shaderReflection);
                        InitRootParameter();
                    }
                }
			}
			void HMDirectX12ShaderObject::Terminate()
			{
			}
			void HMDirectX12ShaderObject::RefConstantBuffer(ComPtr<ID3D12ShaderReflection> refl)
			{
                D3D12_SHADER_DESC desc{};
                refl->GetDesc(&desc);
                for (unsigned int i = 0; i < desc.ConstantBuffers; ++i) {
                    D3D12_SHADER_BUFFER_DESC shaderBufDesc{};
                    auto cbuffer = refl->GetConstantBufferByIndex(i);
                    cbuffer->GetDesc(&shaderBufDesc);
                    std::unordered_map<std::string, std::string> bufferMap;
                    for (auto j = 0; j < shaderBufDesc.Variables; ++j)
                    {
                        D3D12_SHADER_VARIABLE_DESC varDesc{};
                        D3D12_SHADER_TYPE_DESC typeDesc;
                        ID3D12ShaderReflectionVariable* varRefl = cbuffer->GetVariableByIndex(j);
                        ID3D12ShaderReflectionType* varTypeRefl = varRefl->GetType();
                        varRefl->GetDesc(&varDesc);
                        varTypeRefl->GetDesc(&typeDesc);
                        bufferMap[varDesc.Name] = typeDesc.Name;
                    }
                    // バインドポイントの取得
                    for (unsigned int j = 0; j < desc.BoundResources; ++j) {
                        D3D12_SHADER_INPUT_BIND_DESC bindDesc;
                        refl->GetResourceBindingDesc(j, &bindDesc);

                        if (bindDesc.Type == D3D_SIT_CBUFFER && std::string(bindDesc.Name) == std::string(shaderBufDesc.Name)) {
                            m_ConstantBuffers[bindDesc.BindPoint] = bufferMap;
                            break; // マッチしたらループを抜ける 
                        }
                    }
                }
			}
			void HMDirectX12ShaderObject::RefTexture(ComPtr<ID3D12ShaderReflection> refl)
			{
                D3D12_SHADER_DESC desc{};
                refl->GetDesc(&desc);
                for (unsigned int i = 0; i < desc.BoundResources; ++i) {
                    D3D12_SHADER_INPUT_BIND_DESC resDesc;
                    refl->GetResourceBindingDesc(i, &resDesc);
                    // テクスチャまたはサンプラーの場合のみ処理
                    if (resDesc.Type == D3D_SIT_TEXTURE) {
                        m_Textures[resDesc.BindPoint] = resDesc.Name;
                    }
                }
			}
			void HMDirectX12ShaderObject::RefSampler(ComPtr<ID3D12ShaderReflection> refl)
			{
                D3D12_SHADER_DESC desc{};
                refl->GetDesc(&desc);
                for (unsigned int i = 0; i < desc.BoundResources; ++i) {
                    D3D12_SHADER_INPUT_BIND_DESC resDesc;
                    refl->GetResourceBindingDesc(i, &resDesc);
                    // テクスチャまたはサンプラーの場合のみ処理
                    if (resDesc.Type == D3D_SIT_SAMPLER) {
                        m_Textures[resDesc.BindPoint] = resDesc.Name;
                    }
                }
			}
			void HMDirectX12ShaderObject::InitRootParameter()
			{
                std::vector<CD3DX12_DESCRIPTOR_RANGE> tableRanges;

                for (const auto& cb : m_ConstantBuffers) {
                    CD3DX12_DESCRIPTOR_RANGE temp;
                    temp.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, cb.first); // 各CBVに対するレンジ 
                    tableRanges.push_back(temp);
                }
                for (const auto& tex : m_Textures) {
                    CD3DX12_DESCRIPTOR_RANGE temp;
                    temp.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, tex.first); // 各CBVに対するレンジ  
                    tableRanges.push_back(temp);
                }

                // すべてのレンジを含むディスクリプタテーブルを作成
                CD3DX12_ROOT_PARAMETER param;
                param.InitAsDescriptorTable(tableRanges.size(), tableRanges.data(), D3D12_SHADER_VISIBILITY_ALL);
                rootParams.push_back(param);
			}
		}
	}
}