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
			void CreateSceneObject(const TCHAR* sceneJson);
			CORE::HMModSceneManager* _sceneManager;
		};
	}
} /// namespace HARMONY