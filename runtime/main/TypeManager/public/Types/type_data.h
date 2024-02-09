#pragma once
#include<string>

namespace HARMONY
{
	namespace detail
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

		template<typename TYPE>
		struct TYPEMANAGER_API Type_Data
		{
			TYPE_CATEGORY	_typeCategory = TYPE_CATEGORY::MAX;//型のカテゴリー 
			std::string     _name; // 型の名前
			size_t          _size; // 型のサイズ
			Type_Data(std::string name) :_name(name), _size(sizeof(T)) {};
		};
	}
}