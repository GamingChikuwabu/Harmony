#pragma once
#include"IModule.h"
#include"ModuleManager.h"
#include"IRenderingAPI.h"
#include"IShaderObject.h"
#include"IMaterial.h"

namespace HARMONY
{
	namespace CORE
	{
		enum Synchronous
		{
			ASYNC = 0,
			SYNC
		};

		struct Vertex {
			float x, y, z;    // 位置
			float nx, ny, nz; // 法線
			float u, v;       // テクスチャ座標
			// コンストラクタ
			Vertex() : x(0), y(0), z(0), nx(0), ny(0), nz(0), u(0), v(0) {}
		};

		struct MESH {
			// 既存のメンバ変数
			char name[32];
			uint32_t numVertices;
			uint32_t numIndices;
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
			MESH() : numVertices(0), numIndices(0) {
				std::memset(name, 0, 32);
			}
			~MESH() {
			}
		};

		class HMModResourceManager : public IModule
		{
		public:
			HMModResourceManager();
			~HMModResourceManager();
			bool Initialize()override;
			void LoadShader(const char* path, Synchronous synchronous);
			void LoadTexture(const char* path, Synchronous synchronous);
			//void LoadMesh(const char* path, Synchronous synchronous);
			/*void LoadMaterial(const char* path, Synchronous synchronous);
			const MESH* GetMesh(const char* meshname);*/
		private:
			IRenderingAPI* _renderApi;
			//シェーダーオブジェクト
			HMUnorderedMap<HMString, IShaderObject*> _shaderArray;
			//HMUnorderedMap<HMString,MESH*> _meshArray;
			//HMUnorderedMap<HMString, IMaterial*> _materialArray;
		};
	}
} /// namespace HARMONY