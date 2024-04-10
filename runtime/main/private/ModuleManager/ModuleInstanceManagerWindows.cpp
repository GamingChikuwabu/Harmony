#include"ModuleManager/ModuleInstanceManagerWindows.h"
#include"gc_cpp.h"
#include"HMArray.h"
#include"HMUnorderedMap.h"
#include<Windows.h>

namespace HARMONY
{
	namespace DETAIL
	{
		struct ModuleInstanceManagerWindows_impl
		{
			HMUnorderedMap<HMString, HMODULE> _dllHandles;
		};

		ModuleInstanceManagerWindows::ModuleInstanceManagerWindows()
		{
			_impl = new (GC_NEW(ModuleInstanceManagerWindows_impl)) ModuleInstanceManagerWindows_impl();
		}

		bool ModuleInstanceManagerWindows::LoadModule(const TCHAR* path,const TCHAR* moduleName)
		{
			auto handle = LoadLibraryEx(path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
			if (handle)
			{
				_impl->_dllHandles[moduleName] = handle;
				return true;
			}
			return false;
		}

		bool ModuleInstanceManagerWindows::UnLoadModule(const TCHAR* modulemname)
		{
			// モジュール名に対応するハンドルをマップから検索
			auto it = _impl->_dllHandles.find(modulemname);

			// ハンドルが見つかった場合
			if (it != _impl->_dllHandles.end()) {
				// FreeLibraryを呼び出してDLLをアンロード
				if (FreeLibrary(it->second)) {
					// アンロード成功時、マップからも削除
					_impl->_dllHandles.erase(it->first);
					return true; // 成功を示すtrueを返す
				}
			}

			// モジュールが見つからないか、アンロードに失敗した場合はfalseを返す
			return false;
		}
	}
}