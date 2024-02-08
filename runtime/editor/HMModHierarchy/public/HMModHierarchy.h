#pragma once
#ifdef _WIN32
#ifdef HMMODHIERARCHY_EXPORTS 
#define HMMODHIERARCHY_API  __declspec(dllexport) 
#else
#define HMMODHIERARCHY_API  __declspec(dllimport)
#endif // HMMODHIERARCHY_API
#else
#define HMMODHIERARCHY_API
#endif // WIND32

#include"ModuleManager.h"
#include"HMModSceneManager.h"
#include<functional>

namespace HARMONY
{
	namespace EDITOR
	{
		class HMModHierarchy : public IModule
		{
		public:
			HMModHierarchy();
			~HMModHierarchy();
			bool Initialize()override;
		private:
			void CreateSceneObject(const std::vector<char>& data);
			void AddSceneObject(const std::vector<char>& data);
			void SendAddedSceneData(const char* name, const char* parent_name);
			void AddGameObject(const std::vector<char>& data);
			CORE::HMModSceneManager* _sceneManager;
		};
	}
}