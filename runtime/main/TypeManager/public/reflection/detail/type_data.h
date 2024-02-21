#pragma once
#include<string>
#include<type_traits>
#include<bitset>
#include<memory>

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
        constexpr size_t type_trait_count = static_cast<size_t>(type_trait_infos::TYPE_TRAIT_COUNT);

		struct type_data
		{
            std::shared_ptr<type_data> _rawType;        //コンストやポインタが外されたタイプ
            std::shared_ptr<type_data> _wrappedType;    //!ラップされたタイプ
            std::shared_ptr<type_data> _arrayRawType;   //配列の元の型
			std::string _name;                          //型の名前ユーザー登録型じゃない場合はマングルされている可能性がある
            std::bitset<type_trait_count> _info;        //この型のビット情報
            std::size_t _size;                          //この型のサイズ
			bool _isValid;                              //このtype型が有効かを示す
		};

        template<typename T, bool = std::is_same<T,typename std::remove_cv_t<T>>::value>
        struct raw_type_info
        {
            static inline type getType() { return GetInvalidType(); }
        };

        template<typename T>
        struct raw_type_info<T,false>
        {
            static inline type getType() { return type::Get<typename std::remove_cv_t<T>>(); }
        };

        template<typename T, bool = is_wrapper<T>::value>
        struct wrapped_type_info
        {
            static inline type getType() { return GetInvalidType(); }
        };

        template<typename T>
        struct wrapped_type_info<T,false>
        {
            static inline type getType() { return type::Get<typename wrapper_mapper_t<T>>(); }
        };

        template<typename T, bool = std::is_array<T>::value>
        struct array_raw_type_info
        {
            static inline type getType() { return GetInvalidType(); }
        };

        template<typename T>
        struct array_raw_type_info<T, false>
        {
            static inline type getType() { return type::Get<typename std::is_array<T>>(); }
        };

        template<typename T>
        type_data* CreateTypeData()
        {
            auto t = new type_data();
            t->_rawType = std::shared_ptr<type_data>(raw_type_info<T>::getType().GetTypeData());
            return t;
            /*{
                std::shared_ptr<type_data>(raw_type_info<T>::getType().GetTypeData()),
                std::shared_ptr<type_data>(wrapped_type_info<T>::getType().GetTypeData()), 
                std::shared_ptr<type_data>(array_raw_type_info<T>::getType().GetTypeData()),
                typeid(T).name(),
                std::bitset<type_trait_count>(),
                sizeof(T),
                true
            };*/
        }
	}
}