#pragma once
#include<string>
#include<type_traits>
#include<bitset>
#include<memory>

#include"type_trait_info.h"
#include"wrapper_mapper.h"

namespace HARMONY
{
    class type;
	namespace DETAIL
	{
        template<typename T, typename Enable = void>
        struct raw_array_type { using type = std::remove_cv_t<T>; };

        template<typename T>
        struct raw_array_type_impl;

        template<typename T, std::size_t N>
        struct raw_array_type_impl<T[N]> { using type = typename raw_array_type<T>::type; };

        template<typename T>
        struct raw_array_type<T, typename std::enable_if<std::is_array<T>::value>::type>
        {
            using type = typename raw_array_type_impl< std::remove_cv_t<T> >::type;
        };

        template<typename T>
        using raw_array_type_t = typename raw_array_type<T>::type;

        /// @brief 型情報を提供するための構造体です。基本型に対する情報を取得します。
        /// @tparam T 調べる型
        /// @tparam 二番目のテンプレートパラメータは、TがCV修飾（const/volatile）されていないかを確認します。デフォルトでは、Tとその非CV修飾版が同じかどうかを検証します。
        template<typename T, bool = std::is_same<T, typename std::remove_cv_t<T>>::value>
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
            static inline type getType() { return type::Get<typename std::remove_cv_t<T>>(); }
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

		/// @brief 型情報のデータ
		struct type_data
		{
            type_data* _rawType;                        //コンストやポインタが外されたタイプ
            type_data* _wrappedType;                    //!ラップされたタイプ
            type_data* _arrayRawType;                   //配列の元の型
			std::string _name;                          //型の名前ユーザー登録型じゃない場合はマングルされている可能性がある
            TypeTraitBitSet _info;                      //この型のビット情報
            std::size_t _size;                          //この型のサイズ
			bool _isValid;                              //このtype型が有効かを示す
		};

        template<typename T>
        std::unique_ptr<DETAIL::type_data> make_type_data()
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
                        true
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
                    false
                }
            );
            return val.get();
        }
	}
}