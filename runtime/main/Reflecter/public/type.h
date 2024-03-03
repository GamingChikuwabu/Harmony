#pragma once
#include<memory>

namespace HARMONY
{
	class type;
	class property;
	namespace DETAIL
	{
		struct invalid_type {};
		struct type_data;
		template<typename T>
		std::unique_ptr<DETAIL::type_data> make_type_data();
		/// @brief type_dataからtypeを作成する関数
		/// @param _data nullptrなら無効なtype型が作成される
		/// @return type
		inline type CreateType(DETAIL::type_data* _data);

		/// @brief 無効なType型を取得する関数
		/// @return 無効なタイプ型
		inline type GetInvalidType();
	}
	class REFLECTER_API type
	{
	public:
		type(const type& other);

		const char* GetName()const;

		type GetRawType()const;

		type GetWrappedType()const;

		size_t GetSize()const;

		template<typename T>
		static type GetType();

		/// @brief この型が有効かを示す関数
		/// @return 有効ならtrueを
		bool IsValid()const;

		/// @brief この型が算術型かを返す
		/// @return 算術型ならtrue
		bool IsArithmetic()const noexcept;

		/// @brief この型がポインタかを返す
		/// @return ポインタならtrueを
		bool IsPointer()const noexcept;

		/// @brief この型が配列型かを返す
		/// @return 配列ならtrueを
		bool IsArray()const noexcept;

		/// @brief この型がクラス型かを返す
		/// @return クラスならtrue
		bool IsClass()const noexcept;

		/// @brief
		/// @return 
		bool IsEnum()const noexcept;

		/// @brief 関数ポインタか
		/// @return 
		bool IsFunctionPointer()const noexcept;

		/// @brief メンバ変数ポインタか
		/// @return 
		bool IsMemberObjectPointer()const noexcept;

		/// @brief メンバ関数ポインタか
		/// @return 
		bool IsMemberFunctionPointer()const noexcept;

		/// @brief ラップ型か
		/// @return 
		bool IsWrapped()const noexcept;

		/// @brief 一連配列コンテナか
		/// @return 
		bool IsSequentialContainer()const noexcept;

		/// @brief 連想配列コンテナか
		/// @return 
		bool IsAssociativeContainer()const noexcept;
	private:
		type();
		type(DETAIL::type_data* data);
		std::unique_ptr<DETAIL::type_data> data;
		friend DETAIL::type_data;
		friend type GetInvalidType();
		template<typename T>
		friend std::unique_ptr<DETAIL::type_data> DETAIL::make_type_data();
		friend type DETAIL::CreateType(DETAIL::type_data* _data);
	};
}

#include"inl/type.inl"