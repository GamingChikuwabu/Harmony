#pragma once
#include<string_view>
#include<vector>
#include<typeindex>
#include<memory>

namespace HARMONY
{
	class variant;
	class enumeration;
	class constructor;
	class property;
	class instance;

	namespace DETAIL
	{
		struct type_data;
	}

	class TYPEMANAGER_API type
	{
	public:
		/// @brief typeのコピーコンストラクタ
		/// @param othr 
		type(const type& othr);

		/// @brief テンプレートで指定した型のtype型を返す
		/// @tparam T 型
		/// @return TypeManagerなどで登録していない型だと無効なtype型が返される
		template<typename T>
		static type get();

		/// @brief 引数のインスタンスのtype型を返す
		/// @tparam T インスタンスのタイプ
		/// @param object インスタンス
		/// @return 登録されていなかったら無効なタイプ型を返す
		template<typename T>
		static type get(T&& object);

		/// @brief 名前からTypeを作成する
		/// @param name 型の名前
		/// @return 登録されていなかったら無効なタイプ型を返す
		static type getByName(std::string_view name); 

		/// @brief このType型のvariantを作成する
		/// @return 生成に失敗したら無効なvariantを返す
		variant Create();

		/// @brief 引数付きのコンストラクタを実行する場合
		/// @tparam ...Args 引数
		/// @param ...arg 引数
		/// @return 生成に失敗したら無効なvariantを返す
		template<typename... Args>
		variant Create(Args... arg);

		/// @brief コンパイラ依存の型の名前
		/// @return clangやgccでは型名がマングルされる
		std::string_view GetName();

		/// @brief 実行時型情報を取得する関数
		/// @return 
		std::type_index GetTypeID();

		/// @brief 型のサイズ
		/// @return サイズ
		std::size_t GetSizeof()const noexcept;

		/// @brief 有効なType型か
		explicit operator bool()const noexcept;

		/// @brief 配列型の型を返す
		/// @return int[]ならintを返す
		type GetRawType()noexcept;

		/// @brief ラッピングされたインスタンスの型を返す
		/// @return std::uniq_ptr<int> がたならintを返す
		type GetWrappedType()const noexcept;  

		/// @brief enumのラッピングクラスを返す
		/// @return enumじゃない場合は無効型を返す
		enumeration GetEnumeration()const;

		/// @brief コンストラクタのラッピングクラスを返す
		/// @return class型じゃない場合は無効なコンストラクタを返す
		constructor GetConstructor()const noexcept;

		/// @brief 名前指定したクラスプロパティを返す
		/// @param prop_name プロパティの名前
		property GetProperty(std::string_view prop_name)noexcept;

		/// @brief クラスのすべてのプロパティを取得する
		/// @return 
		std::vector<property> GetProperties()noexcept;

		/// @brief インスタンス化したクラスのプロパティの値を返す
		/// @param name プロパティの名前
		/// @param obj インスタンスクラスオブジェクト
		/// @return 値
		variant GetPropertyValue(std::string_view name,instance obj)noexcept; 

		/// @brief インスタンス化したクラスのプロパティの値を
		/// @param name プロパティの名前
		/// @param obj インスタンスクラスオブジェクト
		/// @return 
		bool SetPropertyValue(std::string_view name, instance obj)noexcept;

		/// @brief 型の有効か無効か
		/// @return 結果
		bool isValid()noexcept;

		/// @brief 数値型かを調べる
		/// @return けっか
		bool isArithmetic()noexcept;

		/// @brief enum型かを調べる
		/// @return 結果
		bool isEnumeration()noexcept;

		/// @brief 配列型かを調べる
		/// @return 結果
		bool isArray()noexcept;

		/// @brief クラス型かを調べる
		/// @return 結果
		bool isClass()noexcept;

		/// @brief ラッパー型かを調べる
		/// @return 結果
		bool isWrapped()noexcept;

		/// @brief vectorやlistなどの一連配列かを調べる
		/// @return 結果
		bool isSequential()noexcept;

		/// @brief map,pairなどの
		/// @return 
		bool isAssociation()noexcept;

		/// @brief ポインタ型かを調べる
		/// @return けっか
		bool isPointer()noexcept;

		/// @brief 関数ポインタかを調べる
		/// @return 結果
		bool isFunctionPointer()noexcept;

		/// @brief メンバ変数ポインタかを調べる
		/// @return 結果
		bool isMemberObjectPointer()noexcept;

		/// @brief メンバ関数ポインタか
		/// @return 結果
		bool isMemberFunctionPointer()noexcept;
	private:
		type();
		type(DETAIL::type_data* _data);
		std::unique_ptr<DETAIL::type_data> _data;
	};

	//無効なタイプ型を生成します
	type GetInvalidType();
}

#include"reflection/impl/type_impl.h"