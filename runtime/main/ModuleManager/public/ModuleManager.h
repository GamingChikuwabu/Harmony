#pragma once
#pragma warning(disable:4251)

#include"IModule.h"
#include<memory>
#include<unordered_map>
#include<string>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif 
#include<Windows.h>
#endif // _WIN32


namespace HARMONY 
{
	/// @brief モジュールを管理するクラス
	class MODULEMANAGER_API ModuleManager
	{
	public:
		/// @brief 初期化関数
		/// @return 結果 
		static bool Initialize();

		/// @brief 実行処理 
		/// @return 
		static void Running();

		/// @brief 実行準備処理
		static void Ready();

		/// @brief 更新処理
		static void Update();

		/// @brief 終了処理
		/// @return 
		static void Terminate();

		/// @brief モジュールのポインタを補完管理する
		static bool RegisterModule(IModule* module);

		/// @brief プロジェクトごとの設定ファイルやアセットのルートパス
		/// @return パス
		static const char* GetProjectAssetsPath();

		/// @brief プロジェクトに依存しないアセットのルートパスTextureやマテリアル、シェーダー、モデルなど
		/// @return ルートディレクトリのパス
		static const char* GetAllAssetsRootPath();

		/// @brief Engineのカレントディレクトリ
		/// @return Engineのカレントディレクトリのフルパス
		static const char* GetEnginePath();

		/// @brief コマンドライン引数を解析する関数
		/// @param argc 引数の数
		/// @param argv 引数の配列
		static void CommandLineAnalyze(int argc, void** argv);


		template<class T>
		static T* GetModule()
		{
			for (auto& mod : m_pModuleArray)
			{
				T* retmod = dynamic_cast<T*>(mod);
				if (retmod)
				{
					return retmod;
				}
			}
			return nullptr;
		}
	private:
		//========================================================================
		//メンバ変数
		static inline std::unordered_map<std::string, std::string> m_moduleKind;
		static inline std::vector<IModule*> m_pModuleArray;
#ifdef _WIN32
		static inline std::unordered_map<std::string, HMODULE> m_modulehandole;
#endif // _WIN32
		static inline std::string m_projectAssetsPath = "";
		static inline std::string m_assetsPath = "";
		static inline std::string m_EnginePath = "C:/work/myworkspace/engine/v3_50_00/develop/editor";
		static bool LoadCoreModule();
		static bool LoadCorePluginModule();
		static bool LoadPlatformModule();
		static bool LoadEditorModule();
		static bool LoadModule(const char* path);
	};
}

#define RegisterModuleClass(moduleclass)\
	namespace {static bool moduleactive = HARMONY::ModuleManager::RegisterModule(new moduleclass());}