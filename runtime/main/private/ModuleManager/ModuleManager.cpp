#include<filesystem>
#include <iostream>

#include"ModuleManager/ModuleManager.h"
#include"EventManager/EventManager.h"
#include"ModuleManager/IModule.h"
#include"HMArray.h"
#include"HMString.h"

#ifdef _WIN32
#include "ModuleInstanceManagerWindows.h"
#endif // _WIN32


namespace HARMONY
{
	bool ModuleManager::Initialize()
	{
		_impl = new (GC_NEW(DETAIL::ModuleInstanceManagerWindows)) DETAIL::ModuleInstanceManagerWindows();

		LoadPlatformModule();
		LoadCoreModule();
		LoadCorePluginModule();
		LoadEditorModule();

		for (int i = 0; i < _pModuleArray.GetSize(); i++)
		{
			if (!_pModuleArray[i]->AwakeInitialize())
			{
				return false;
			}
		}
		for (const auto& mod : _pModuleArray)
		{
			if (!mod->Initialize())
			{
				return false;
			}
		}
		for (const auto& mod : _pModuleArray)
		{
			if (!mod->LateInitialize())
			{
				return false;
			}
		}
		HARMONY::EventManager::GetEvent<>(TSTR("OnReady")).Add(ModuleManager::Ready);
		HARMONY::EventManager::GetEvent<>(TSTR("OnUpdate")).Add(ModuleManager::Update); 
		return true;
	}

	void ModuleManager::Ready()
	{
		for (const auto& mod : _pModuleArray)
		{
			mod->Ready();
		}
	}

	void ModuleManager::Update()
	{
		for (const auto& mod : _pModuleArray)
		{
			mod->Update();
		}
	}

	void ModuleManager::Terminate()
	{
		for (auto& modules : _pModuleArray)
		{
			modules->Terminate(); 
		}
	}

	const TCHAR* ModuleManager::GetProjectAssetsPath()
	{
		return _projectAssetsPath;
	}

	
	const TCHAR* ModuleManager::GetAllAssetsRootPath()
	{
		return _assetsPath;
	}

	const TCHAR* ModuleManager::GetEnginePath()
	{
		return _EnginePath;
	}

	
	void ModuleManager::CommandLineAnalyze(int argc, void** argv)
	{
		//通常起動
		if (argc == 1)
		{
			/*std::filesystem::path currentPath = std::filesystem::current_path();
			m_projectPath = currentPath.string();
			m_assetsPath = currentPath.string();*/
			_projectAssetsPath = TSTR("C:/work/myworkspace/ProjectsRoot/Sample/project");
			_assetsPath = TSTR("C:/work/myworkspace/ProjectsRoot/Sample/assets");
		}
		else//Runtimeとして起動
		{
			_projectAssetsPath = TSTR("C:/work/myworkspace/engine/v3_60_00/develop/editor");
			_assetsPath = TSTR("C:/work/myworkspace/ProjectsRoot/Sample/assets");
		}
	}

	bool ModuleManager::RegisterModule(IModule* moduleclass)
	{
		_pModuleArray.Add(moduleclass);
		return true;
	}

	bool ModuleManager::LoadCoreModule()
	{
		std::filesystem::path path = _EnginePath;
		path.append("Engine").append("core");
		if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
			std::cerr << "ディレクトリが存在しないか、ディレクトリではありません: " << path << std::endl;
			return false;
		}
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_regular_file() && entry.path().extension() == ".dll") {
				LoadModule(entry.path().c_str());
			}
		}
		return true;
	}

	bool ModuleManager::LoadCorePluginModule()
	{
		std::filesystem::path path = _EnginePath;
		path.append("Engine").append("coreplugin");
		if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
			std::cerr << "ディレクトリが存在しないか、ディレクトリではありません: " << path << std::endl;
			return false;
		}
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_regular_file() && entry.path().extension() == ".dll") {
				LoadModule(entry.path().c_str());
			}
		}
		return true;
	}

	bool ModuleManager::LoadPlatformModule()
	{
		std::filesystem::path path = _EnginePath;
#ifdef _WIN32
		path.append("Engine").append("platform").append("windows");
#endif // _WIN32
		if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
			std::cerr << "ディレクトリが存在しないか、ディレクトリではありません: " << path << std::endl;
			return false;
		}
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_regular_file() && entry.path().extension() == ".dll") {
				LoadModule(entry.path().c_str());
			}
		}
		return true;
	}

	bool ModuleManager::LoadEditorModule()
	{
		std::filesystem::path path = _EnginePath;
		path.append("Engine").append("editor");
		if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
			std::cerr << "ディレクトリが存在しないか、ディレクトリではありません: " << path << std::endl;
			return false;
		}
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_regular_file() && entry.path().extension() == ".dll") {
				LoadModule(entry.path().c_str()); 
			}
		}
		return true;
	}

	bool ModuleManager::LoadModule(const TCHAR* path)
	{
		std::filesystem::path path_to_dll = path;

		_impl->LoadModule(path, path_to_dll.filename().c_str());
		return true;
	}
}