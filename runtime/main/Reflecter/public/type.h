#pragma once
#include<string>
#include<typeinfo>
#include<memory>

namespace HARMONY
{
	class Type;
	namespace DETAIL
	{
		struct invalid_type {};
		struct TypeData;
		template<typename T>
		std::unique_ptr<DETAIL::TypeData> make_type_data();
		/// @brief type_dataからtypeを作成する関数
		/// @param _data nullptrなら無効なtype型が作成される
		/// @return type
		inline Type CreateType(DETAIL::TypeData* _data);

		/// @brief 無効なType型を取得する関数
		/// @return 無効なタイプ型
		inline Type GetInvalidType();
	}
	class REFLECTER_API Type
	{
	public:
		/// @brief コピーコンストラクタ
		/// @param other コピー元
		Type(const Type& other);

		/// @brief 代入用の演算子
		/// @param other 代入元
		void operator=(const Type& other);

		bool operator==(const Type& other);

		bool operator!=(const Type& other);

		/// @brief テンプレート引数の型のtype型を返す
		/// @tparam T 生成する型
		/// @return 作成に失敗したら無効なtype型が返される
		template<typename T>
		static Type Get();

		/// @brief 型の名前を返す
		/// @return Windows以外はマングルされているので注意
		std::string GetName();

		/// @brief この型のサイズ
		/// @return サイズ
		size_t GetSizeOf()const noexcept;

		/// @brief この型がラップ型ならラップされたtypeを返す std::uniq_ptr<int>ならint
		/// @return ラップじゃなければこのtype型をそのまま返す
		Type GetWrappedType()const;

		Type GetRawType()const;

		Type GetArrayRawType()const;

		Type GetTypeByName(const char* name);

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

		/// @brief 使用しないでください
		/// @return 
		DETAIL::TypeData* GetData();

		Type();
	private:
		Type(DETAIL::TypeData* data);
		friend DETAIL::TypeData;
		friend Type GetInvalidType();
		template<typename T>
		friend std::unique_ptr<DETAIL::TypeData> DETAIL::make_type_data();
		friend Type DETAIL::CreateType(DETAIL::TypeData* _data);
	private:
		DETAIL::TypeData* _data;
	};
}