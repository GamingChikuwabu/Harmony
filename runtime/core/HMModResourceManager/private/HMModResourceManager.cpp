#include"HMModResourceManager.h"
#include"IShaderObject.h"
#include<filesystem>
#include<fstream>

namespace HARMONY
{
	namespace CORE
	{
        bool ReadFromFile(const std::string& filename, MESH& mesh) {
            std::ifstream inFile(filename, std::ios::binary);
            if (!inFile) {
                return false;
            }
            // メッシュの名前、頂点数、インデックス数を読み込む
            inFile.read(mesh.name, 32);
            inFile.read(reinterpret_cast<char*>(&mesh.numVertices), sizeof(mesh.numVertices));
            inFile.read(reinterpret_cast<char*>(&mesh.numIndices), sizeof(mesh.numIndices));

            // 頂点データを読み込む
            mesh.vertices.resize(mesh.numVertices);
            for (uint32_t i = 0; i < mesh.numVertices; ++i) {
                Vertex& v = mesh.vertices[i];
                inFile.read(reinterpret_cast<char*>(&v), sizeof(Vertex));
            }

            // インデックスデータを読み込む
            mesh.indices.resize(mesh.numIndices);
            inFile.read(reinterpret_cast<char*>(mesh.indices.data()), mesh.numIndices * sizeof(uint32_t));
            inFile.close();
            return true;
        }
		RegisterModuleClass(HMModResourceManager);
		HMModResourceManager::HMModResourceManager():_renderApi(nullptr)
		{
		}
		HMModResourceManager::~HMModResourceManager()
		{
		}
        bool HMModResourceManager::Initialize()
        {
            _renderApi = ModuleManager::GetModule<IRenderingAPI>();
            if (!_renderApi)
            {
                return false;
            }
            return true;
        }
        void HMModResourceManager::LoadShader(const char* path, Synchronous synchronous)
        {
            IShaderObject* shaderObject = reinterpret_cast<IShaderObject*>(_renderApi->CreateResource(ResourceType::ShaderObject));
            shaderObject->InitShaderObject(path);
            _shaderArray[std::filesystem::path(path).filename().c_str()] = shaderObject;
        }
        /*void HMModResourceManager::LoadMesh(const char* path, Synchronous synchronous)
        {
            MESH mesh;
            ReadFromFile(path, mesh);
            _meshArray[mesh.name] = std::make_shared<MESH>(mesh);
        }*/
        void HMModResourceManager::LoadTexture(const char* path, Synchronous synchronous)
        {

        }
        /*void HMModResourceManager::LoadMaterial(const char* path, Synchronous synchronous)
        {
             _materialArray[""] = std::reinterpret_pointer_cast<IMaterial>(_renderApi->CreateResource(ResourceType::Material)); 
        }*/
        /*const MESH* HMModResourceManager::GetMesh(const char* meshname)
        {
            return _meshArray[meshname].get();
        }*/
	}
}