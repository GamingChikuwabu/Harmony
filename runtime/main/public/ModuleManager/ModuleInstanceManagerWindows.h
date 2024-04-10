#pragma once
#include"ModuleInstanceManagerBase.h"

namespace HARMONY
{
	namespace DETAIL
	{
		struct ModuleInstanceManagerWindows_impl;
		class ModuleInstanceManagerWindows : public ModuleInstanceManagerBase
		{
		public:
			ModuleInstanceManagerWindows();
			/// @brief dllやso,dylibなどを読み込む関数
			/// @param path ファイルのパス
			/// @return モジュールの読み込みに成功したらIModuleのインスタンスが返される
			virtual bool LoadModule(const TCHAR* path,const TCHAR* moduleName);

			/// @brief 名前で指定したモジュールをアンロードする
			/// @param modulemname アンロードしたいモジュールの名前
			/// @return 結果
			virtual bool UnLoadModule(const TCHAR* modulemname);
		private:
			ModuleInstanceManagerWindows_impl* _impl;
		};
	}
}