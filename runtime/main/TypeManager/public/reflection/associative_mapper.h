#pragma once
#include<type_traits>

namespace HARMONY
{
	//ラッパータイプじゃない場合に代わりに宣言するためのダミー型
	struct invalid_associative_type { };

	template<typename T>
	struct associative_container_mapper
	{
		using is_valid = std::false_type;
	};
}

#include"reflection/detail/impl/associative_mapper_impl.h"