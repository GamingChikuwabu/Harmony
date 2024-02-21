#pragma once
#include<string>
#include<memory>

namespace HARMONY
{
	namespace DETAIL
	{
		struct invalid_type {};
		struct type_data;
		template<typename T>
		std::unique_ptr<DETAIL::type_data> make_type_data();
	}
	class TYPEMANAGER_API type
	{
	public:
		/// @brief コピーコンストラクタ
		/// @param other コピー元
		type(const type& other);

		/// @brief 代入用の演算子
		/// @param other 代入元
		void operator=(const type& other);

		/// @brief テンプレート引数の型のtype型を返す
		/// @tparam T 生成する型
		/// @return 作成に失敗したら無効なtype型が返される
		template<typename T>
		static type Get();

		/// @brief 型の名前を返す
		/// @return Windows以外はマングルされているので注意
		std::string GetName();

		/// @brief この型のサイズ
		/// @return サイズ
		size_t GetSizeOf()const noexcept;

		/// @brief この型がラップ型ならラップされたtypeを返す std::uniq_ptr<int>ならint
		/// @return ラップじゃなければこのtype型をそのまま返す
		type GetWrappedType()const;

		/// @brief 比較演算子
		/// @param _this 比較対象一
		/// @param other 比較対象二
		/// @return 比較の結果
		TYPEMANAGER_API friend bool operator==(const type& _this, const type& other);

		/// @brief 比較演算子
		/// @param _this 比較対象一
		/// @param other 比較対象二
		/// @return 比較の結果
		TYPEMANAGER_API friend bool operator!=(const type& _this, const type& other);

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
		friend DETAIL::type_data;
		friend type GetInvalidType();
		template<typename T>
		friend std::unique_ptr<DETAIL::type_data> DETAIL::make_type_data();
	private:
		DETAIL::type_data* _data;
	};
	type GetInvalidType();
}

#include"reflection/impl/type_impl.h"