#pragma once
#include<d3d12.h>
#include<wrl/client.h>
#include<memory>
#include"IConstantBuffer.h"



using Microsoft::WRL::ComPtr;

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			template<class T>
			class HMDirectX12ConstantBuffer : public IConstantBuffer<T>
			{
			public:
				HMDirectX12ConstantBuffer() {};
				~HMDirectX12ConstantBuffer() {};
				bool initialize(T data)override;
			private:

			};

			template<class T>
			inline bool HMDirectX12ConstantBuffer<T>::initialize(T data)
			{
				auto _renderApi = ModuleManager::GetModule<IRenderingAPI>();
				if (!_renderApi)
				{
					return false;
				}
				auto dxdevice = static_cast<HMModDirectX12*>(_renderApi);
				auto& _descripta = dxdevice.GetDescriptorPool();
				// PoolObjectの作成
				std::shared_ptr<PoolObject> poolObj;
				descriptorPool.CreatePoolObject(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, poolObj);
				return false;
			}
		}
	}
}