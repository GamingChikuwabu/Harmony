#pragma once
#include<string>
#include<type_traits>
#include <bitset>

namespace HARMONY
{
	namespace DETAIL
	{
        enum class type_trait_infos : std::size_t
        {
            is_class = 0,
            is_enum,
            is_array,
            is_pointer,
            is_arithmetic,
            is_function_pointer,
            is_member_object_pointer,
            is_member_function_pointer,
            is_associative_container,
            is_sequential_container,
            is_template_instantiation,
            is_wrappermapper,
            TYPE_TRAIT_COUNT
        };

        // access_levelの値の数を取得
        constexpr size_t access_level_count = static_cast<size_t>(type_trait_infos::TYPE_TRAIT_COUNT);

		struct type_data
		{
            // アクセスレベルを管理するためのビットセット
			std::string _name;
            std::bitset<access_level_count> _info;
			bool _isValid;
            std::size_t _size;
		};
	}
}