#pragma once
#include<string>
#include<type_traits>
#include<unordered_map>
#include<typeindex>
#include"Types/type.h"

namespace HARMONY
{
	namespace DETAIL
	{
		// 型の種類を表す列挙体
		enum class TYPE_CATEGORY {
			TYPE_ARITHMETIC,//int,floatなどの算術型
			TYPE_ARRAY,     // 配列型
			TYPE_ENUM,      // Enum型
			TYPE_STRING,    //文字列型
			TYPE_OBJECT,    // classやstructなどの規定値以外
			MAX
		};

		
		struct TYPEMANAGER_API Type_Data
		{
			TYPE_CATEGORY	_typeCategory;//型のカテゴリー 
			std::string     _name; // 型の名前
			size_t          _size; // 型のサイズ
			std::type_index _index;
			template<typename TYPE>
			void init(std::string name)
			{
				_name = name;
				_size = sizeof(TYPE);
				_index = typeid(TYPE);
				_typeMap[_index] = *this;
				if constexpr (std::is_arithmetic_v<TYPE>)
					_typeCategory = TYPE_CATEGORY::TYPE_ARITHMETIC;
				else if constexpr (std::is_class_v<TYPE>)
					_typeCategory = TYPE_CATEGORY::TYPE_OBJECT;
				else if constexpr (std::is_array_v<TYPE>)
					_typeCategory = TYPE_CATEGORY::TYPE_ARRAY;
				else if constexpr (std::is_enum_v<TYPE>)
					_typeCategory = TYPE_CATEGORY::TYPE_ENUM;
			}
			// 型情報からTypeBaseオブジェクトへのマッピングを保持するためのマップ
			static inline std::unordered_map<std::type_index, Type> _typeMap;
		};
	}
}