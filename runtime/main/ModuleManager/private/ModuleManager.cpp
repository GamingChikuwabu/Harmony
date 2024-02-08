#include "ModuleManager.h"
#include"EventManager.h"
#include<Windows.h>
#include<filesystem>
#include <iostream>

namespace HARMONY
{
	bool ModuleManager::Initialize()
	{
		LoadPlatformModule();
		LoadCoreModule();
		LoadCorePluginModule();
		LoadEditorModule();
		for (int i = 0; i < m_pModuleArray.size(); i++)
		{
			if (!m_pModuleArray[i]->AwakeInitialize())
			{
				return false;
			}
		}
		for (const auto& mod : m_pModuleArray)
		{
			if (!mod->Initialize())
			{
				return false;
			}
		}
		for (const auto& mod : m_pModuleArray)
		{
			if (!mod->LateInitialize())
			{
				return false;
			}
		}
		HARMONY::EventManager::GetEvent<>("OnReady").Add(ModuleManager::Ready);
		HARMONY::EventManager::GetEvent<>("OnUpdate").Add(ModuleManager::Update); 
		return true;
	}

	void ModuleManager::Ready()
	{
		for (const auto& mod : m_pModuleArray)
		{
			mod->Ready();
		}
	}

	void ModuleManager::Update()
	{
		for (const auto& mod : m_pModuleArray)
		{
			mod->Update();
		}
	}

	void ModuleManager::Terminate()
	{
		for (auto& modules : m_pModuleArray)
		{
			modules->Terminate(); 
			delete modules;
		}
	}

	const char* ModuleManager::GetProjectAssetsPath()
	{
		return m_projectAssetsPath.c_str();
	}

	
	const char* ModuleManager::GetAllAssetsRootPath()
	{
		return m_assetsPath.c_str();
	}

	const char* ModuleManager::GetEnginePath()
	{
		return m_EnginePath.c_str();
	}

	
	void ModuleManager::CommandLineAnalyze(int argc, void** argv)
	{
		//通常起動
		if (argc == 1)
		{
			/*std::filesystem::path currentPath = std::filesystem::current_path();
			m_projectPath = currentPath.string();
			m_assetsPath = currentPath.string();*/
			m_projectAssetsPath = "C:/work/myworkspace/ProjectsRoot/Sample/project";
			m_assetsPath = "C:/work/myworkspace/ProjectsRoot/Sample/assets";

		}
		else//Runtimeとして起動
		{
			m_projectAssetsPath = "C:/work/myworkspace/engine/v3_50_00/develop/editor";
			m_assetsPath = "C:/work/myworkspace/ProjectsRoot/Sample/assets";
		}
	}

	bool ModuleManager::RegisterModule(IModule* moduleclass)
	{
		m_pModuleArray.push_back((moduleclass));
		return true;
	}

	bool ModuleManager::LoadCoreModule()
	{
		std::filesystem::path path = m_EnginePath;
		path.append("Engine").append("core");
		if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
			std::cerr << "ディレクトリが存在しないか、ディレクトリではありません: " << path << std::endl;
			return false;
		}
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_regular_file() && entry.path().extension() == ".dll") {
				LoadModule(entry.path().string().c_str());
			}
		}
		return true;
	}

	bool ModuleManager::LoadCorePluginModule()
	{
		std::filesystem::path path = m_EnginePath;
		path.append("Engine").append("coreplugin");
		if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
			std::cerr << "ディレクトリが存在しないか、ディレクトリではありません: " << path << std::endl;
			return false;
		}
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_regular_file() && entry.path().extension() == ".dll") {
				LoadModule(entry.path().string().c_str());
			}
		}
		return true;
	}

	bool ModuleManager::LoadPlatformModule()
	{
		std::filesystem::path path = m_EnginePath;
#ifdef _WIN32
		path.append("Engine").append("platform").append("windows");
#endif // _WIN32
		if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
			std::cerr << "ディレクトリが存在しないか、ディレクトリではありません: " << path << std::endl;
			return false;
		}
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_regular_file() && entry.path().extension() == ".dll") {
				LoadModule(entry.path().string().c_str()); 
			}
		}
		return true;
	}

	bool ModuleManager::LoadEditorModule()
	{
		std::filesystem::path path = m_EnginePath;
		path.append("Engine").append("editor");
		if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
			std::cerr << "ディレクトリが存在しないか、ディレクトリではありません: " << path << std::endl;
			return false;
		}
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_regular_file() && entry.path().extension() == ".dll") {
				LoadModule(entry.path().string().c_str());
			}
		}
		return true;
	}

	bool ModuleManager::LoadModule(const char* path)
	{
		std::filesystem::path path_to_dll = path;
#ifdef _WIN32
		m_modulehandole[path_to_dll.filename().stem().string()] = LoadLibraryEx(path_to_dll.wstring().c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
#endif
		return true;
	}
}