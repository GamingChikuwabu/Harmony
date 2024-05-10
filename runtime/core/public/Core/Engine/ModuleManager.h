#pragma once

namespace HARMONY
{
	class CORE_API ModuleManager
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
		/*template<class T>*/
		/*static T* GetModule()
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
		}*/
	};
}