#pragma once
#include"Class/Class.h"

namespace HARMONY
{
	class REFLECTION_API ScriptArray
	{
	public:
		template<typename Array, typename T>
		ScriptArray(Array* instance);
		size_t GetSize();
		void* GetData();
		Class* GetInnerClass();//クラスじゃない場合はnullptr
	private:
		void* instance; // Array のインスタンスへのポインタ
		Class* _innerClass;
		size_t(*getSizeFunc)(void*); // サイズを取得する関数ポインタ
		void* (*getDataFunc)(void*); // データの先頭を取得する関数ポインタ
	};
}