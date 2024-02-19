#pragma once
#include<string>
#include<vector>
#include<functional>
#include<utility>

namespace HARMONY
{
	class variant;
	class enumeration;
	class constructor;
	class property;
	class method;
	class instance;
	class type;
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

			TYPE_TRAIT_COUNT
		};

		enum class access_info
		{
			is_public,
			is_protected,
			is_private,
			is_readonry
		};

		struct enumeration_data
		{
			type		_type;//型
			std::string _typename;	//enumの型の名前
			uint16_t	_size;		//enumの要素数
			std::unordered_map<uint16_t, std::string> _valueNamePair;//enumの要素の値と名前のペア
		};

		struct property_data
		{
			std::string _name;
			access_info _accinfo;
			type        _type;
			std::function<variant(instance)>		_getter;
			std::function<void(instance, variant)>	_setter;
		};

		//型情報
		struct class_data
		{
			std::string					_name; //ユーザー定義の名前
			std::string					_typename;//コンパイラ依存の名前
			std::vector<type>			_baseType;//このクラスの基底クラスタイプ
			std::vector<type>			_derivedType;//このクラスの派生タイプ
			std::vector<constructor>	_constructor;//このクラスのコンストラクタ
			std::vector<property>		_memberProperty;//このクラスのメンバ変数
			std::vector<method>			_memberMethod;//このクラスのメンバ関数
		};

		struct type_data
		{
			std::string _typename;//コンパイラ依存の名前

			type_trait_infos _typeTrait;
			bool isValid;
			
		}; 
	}
}