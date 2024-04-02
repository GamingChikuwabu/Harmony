#include"Property/ScriptArray.h"
#pragma once
#include"HMArray.h"


namespace HARMONY 
{
	template<typename Array, typename T>
	inline ScriptArray::ScriptArray(Array* instance)
	:_innerClass(_innerClass)
	{
		// サイズを取得する関数ポインタをセットします。
		getSizeFunc = [](void* inst) -> size_t {
			return static_cast<Array*>(inst)->GetSize();
			};

		// データの先頭を取得する関数ポインタをセットします。
		getDataFunc = [](void* inst) -> void* {
			return static_cast<Array*>(inst)->GetData();
			};

		// インスタンスポインタを保存します。
		this->instance = instance;
		
	}
	

	template<typename Array>
	class ScriptArrayDerived{};

	template<typename T>
	class ScriptArrayDerived<HMArray<T>>
	{
	public:
		static size_t GetSize(HMArray<T>& instance)
		{
			return instance.getSize();
		}
		static void* GetData(HMArray<T>& instance)
		{
			return (void*)instance.GetData();
		}
	};
}