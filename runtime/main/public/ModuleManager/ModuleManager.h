#pragma once
#pragma warning(disable:4251)
#include"ModuleInstanceManagerBase.h"
#include"IModule.h"

namespace HARMONY 
{
	struct ModuleManager_impl;
	/// @brief モジュールを管理するクラス
	class UTILITY_API ModuleManager
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
		static const TCHAR* GetProjectAssetsPath();

		/// @brief プロジェクトに依存しないアセットのルートパスTextureやマテリアル、シェーダー、モデルなど
		/// @return ルートディレクトリのパス
		static const TCHAR* GetAllAssetsRootPath();

		/// @brief Engineのカレントディレクトリ
		/// @return Engineのカレントディレクトリのフルパス
		static const TCHAR* GetEnginePath();

		/// @brief コマンドライン引数を解析する関数
		/// @param argc 引数の数
		/// @param argv 引数の配列
		static void CommandLineAnalyze(int argc, void** argv);

		template<class T>
		static T* GetModule()
		{
			for (auto& mod : _pModuleArray)
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
		static inline DETAIL::ModuleInstanceManagerBase* _impl;
		static inline HMArray<IModule*> _pModuleArray;
		static inline const TCHAR* _projectAssetsPath;
		static inline const TCHAR* _assetsPath;
		static inline const TCHAR* _EnginePath = L"C:/work/myworkspace/engine/v3_60_00/develop/editor";
	private:
		static bool LoadCoreModule();
		static bool LoadCorePluginModule();
		static bool LoadPlatformModule();
		static bool LoadEditorModule();
		static bool LoadModule(const TCHAR* path);
	};
}

#define RegisterModuleClass(moduleclass)\
	namespace {static bool moduleactive = HARMONY::ModuleManager::RegisterModule(new (GC_NEW(moduleclass)) moduleclass());}