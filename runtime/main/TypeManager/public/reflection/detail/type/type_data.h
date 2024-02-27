#pragma once
#include<string>
#include<type_traits>
#include<bitset>
#include<memory>
#include<vector>

#include"type_trait_info.h"
#include"wrapper_mapper.h"
#include"detail/type_traits/misc_type_traits.h"
#include"detail/type_traits/array_traits.h"
#include"property.h"

namespace HARMONY
{
    class type;
	namespace DETAIL
	{
        
        // end namespace impl
        /// @brief 型情報を提供するための構造体です。基本型に対する情報を取得します。
        /// @tparam T 調べる型
        /// @tparam 二番目のテンプレートパラメータは、TがCV修飾（const/volatile）されていないかを確認します。デフォルトでは、Tとその非CV修飾版が同じかどうかを検証します。
        template<typename T, bool = std::is_same<T, typename DETAIL::raw_type_t<T>>::value>
        struct raw_type_info
        {
            /// @brief 型の情報を取得します。
            /// @return 常に無効な型情報を返します。
            static inline type getType() { return GetInvalidType(); }
        };

        template<typename T>
        struct raw_type_info<T, false>
        {
            /// @brief 型の情報を取得します。
            /// @return CV修飾を除去した型の情報を返します。
            static inline type getType() { return type::Get<DETAIL::raw_type_t<T>>(); }
        };

        /// @brief ラップされた型に対する情報を提供するための構造体です。
        /// @tparam T 調べる型
        /// @tparam 二番目のテンプレートパラメータは、Tがラッパー型かどうかを確認します。デフォルトでは、Tがラッパー型かどうかを検証します。
        template<typename T, bool = is_wrapper<T>::value>
        struct wrapped_type_info
        {
            /// @brief 型の情報を取得します。
            /// @return 常に無効な型情報を返します。
            static inline type getType() { return type::Get<wrapper_mapper_t<T>>(); }
        };

        template<typename T>
        struct wrapped_type_info<T, false>
        {
            /// @brief ラップされた型の情報を取得します。
            /// @return ラッパー型からマップされた実際の型の情報を返します。
            static inline type getType() { return GetInvalidType(); }
        };

        /// @brief 配列型に対する情報を提供するための構造体です。
        /// @tparam T 調べる型
        /// @tparam 二番目のテンプレートパラメータは、Tが配列型かどうかを確認します。デフォルトでは、Tが配列型かどうかを検証します。
        template<typename T, bool = std::is_array<T>::value>
        struct array_raw_type_info
        {
            /// @brief 型の情報を取得します。
            /// @return 常に無効な型情報を返します。
            static inline type getType() { return type::Get<raw_array_type_t<T>>(); }
        };

        template<typename T>
        struct array_raw_type_info<T, false>
        {
            /// @brief 配列型の情報を取得します。
            /// @return 配列型の情報を返します。実際には、std::is_arrayを使用した型のチェック結果を返しますが、これは意図した動作ではありません。
            static inline type getType() { return GetInvalidType(); }
        };

        struct class_data
        {
            std::vector<type>           m_base_types;
            std::vector<type>           m_derived_types;
            std::vector<property>       m_properties;
        };

        template<typename T>
        inline class_data& GetClassData() {
            static std::unique_ptr<class_data> data;
            if (data)
            {
                return(*data.get());
            }
            else
            {
                data = std::make_unique<class_data>();
                return(*data.get());
            }
        }
       
        namespace impl
        {
            using get_class_data_func = class_data & (*)(void);
        }

		/// @brief 型情報のデータ
		struct TYPEMANAGER_API type_data
		{
            type_data* _rawType;                        //コンストやポインタが外されたタイプ
            type_data* _wrappedType;                    //ラップされたタイプ
            type_data* _arrayRawType;                   //配列の元の型
			std::string _name;                          //型の名前ユーザー登録型じゃない場合はマングルされている可能性がある
            TypeTraitBitSet _info;                      //この型のビット情報
            std::size_t _size;                          //この型のサイズ
			bool _isValid;                              //このtype型が有効かを示す
            impl::get_class_data_func _getClassDataFunc;//この型のクラス情報を取得する関数ポインタ
		};

        template<typename T>
        inline std::unique_ptr<DETAIL::type_data> make_type_data()
        {
            auto val = std::unique_ptr<type_data>
                (
                    new type_data
                    {
                        raw_type_info<T>::getType()._data,
                        wrapped_type_info<T>::getType()._data,
                        array_raw_type_info<T>::getType()._data,
                        typeid(T).name(),
                        GetBitSet<T>(), 
                        sizeof(T),
                        true,
                        &GetClassData<T>
                    }
                );
            return val;
        };
        

        static inline type_data* GetInvalidTypeData()
        {
            static const auto val = std::unique_ptr<type_data>(
                new type_data
                {
                    nullptr,
                    nullptr,
                    nullptr,
                    "",
                    GetBitSet<int>(),
                    0,
                    false,
                    nullptr
                }
            );
            return val.get();
        }
	}
}