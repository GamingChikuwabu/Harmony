#pragma once
#include"HMString.h"

namespace HARMONY
{
	class IModule;
	namespace DETAIL
	{
		class ModuleInstanceManagerBase 
		{
		public:
			/// @brief dllやso,dylibなどを読み込む関数
			/// @param path ファイルのパス
			/// @return モジュールの読み込みに成功したらIModuleのインスタンスが返される
			virtual bool LoadModule(const TCHAR* path,const TCHAR* moduleName) = 0;

			/// @brief 名前で指定したモジュールをアンロードする
			/// @param modulemname アンロードしたいモジュールの名前
			/// @return 結果
			virtual bool UnLoadModule(const TCHAR* modulemname) = 0;
		};
	}
}