#pragma once

namespace HARMONY
{
	class REFLECTION_API ScriptArray
	{
	public:
		template<typename Array>
		ScriptArray(Array* instance);
		size_t GetSize();
		void* GetData();
	private:
		void* instance; // Array のインスタンスへのポインタ
		size_t(*getSizeFunc)(void*); // サイズを取得する関数ポインタ
		void* (*getDataFunc)(void*); // データの先頭を取得する関数ポインタ
	};
}

#include"detail/ScriptArray_impl.inl"