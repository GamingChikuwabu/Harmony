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
		struct TYPEMANAGER_API Type_Data
		{
			Type_Data(TYPE_CATEGORY cate, std::string name, size_t size, const std::type_index& index)
				:_typeCategory(cate)
				, _name(name)
				,_size(size)
				, _index(index)
			{};
			TYPE_CATEGORY	_typeCategory;//型のカテゴリー 
			std::string     _name; // 型の名前
			size_t          _size; // 型のサイズ
			std::type_index _index;
			static inline std::unordered_map<std::string, Type> _typeMap;// 型情報からTypeBaseオブジェクトへのマッピングを保持するためのマップ
		};
	}
}