#pragma once
#include"ITexture2D.h"
#include<d3d12.h>
#include<wrl/client.h>
#include"HMDirectX12DescriptorPool.h"

using Microsoft::WRL::ComPtr;

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			class HMDirectX12Texture2D : public ITexture2D
			{
			public:
				HMDirectX12Texture2D();
				~HMDirectX12Texture2D();

				// 空のテクスチャの生成
				void CreateEmptyTexture(int width, int height, FORMAT format, TEXTUREUSE useflag);

				// レンダーターゲットとしての設定
				void SetupAsRenderTarget();
				
				
			private:
				ComPtr<ID3D12Resource>      _textureResource;
				std::shared_ptr<PoolObject> _srvObject;
			};
		}
	}
}