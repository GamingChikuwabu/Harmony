#pragma once
#include<type_traits>
#include<map>
#include<unordered_map>

namespace HARMONY
{
	//ラッパータイプじゃない場合に代わりに宣言するためのダミー型
	struct invalid_associative_type { };

	template<typename T>
	struct associative_mapper
	{
		using type = T;
		
	};
}