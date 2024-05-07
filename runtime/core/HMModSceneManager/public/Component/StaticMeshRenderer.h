#pragma once
#include"Renderer.h"
#include"Utility.hpp"

namespace HARMONY
{
	namespace CORE
	{
		struct World
		{
			 MATH::Matrix4x4 _worldMatrix;
		};

		class StaticMeshRenderer : public Renderer
		{
		public:
			StaticMeshRenderer();
			~StaticMeshRenderer();
			void OnRender(const class ICommandBuffer* commandbuffer)override;
		private:
			IVertexBuffer<StaticMeshVertex_1>*	_vertexBuffer;			//頂点バッファ
			IIndexBuffer*						_indexBuffer;			//インデックスバッファ
			IConstantBuffer<World>*				_worldConstantBuffer;	//コンスタントバッファ
			IMaterial*							_material;				//マテリアル
		};
	}
}