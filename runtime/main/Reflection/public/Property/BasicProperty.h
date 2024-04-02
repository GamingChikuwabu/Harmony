#pragma once
#include"Property/Property.h"
#include<functional>

namespace HARMONY
{
	template<typename T>
	class BasicProperty: public Property
	{
	public:
		/// @brief メンバポインタを使用したアクセス方法用のコンストラクタ
		/// @tparam C クラスの型
		/// @param name クラスの名前
		/// @param memberPtr メンバのオフセット
		template<typename C>
		BasicProperty(const TCHAR* name,size_t offset);

		template<typename C>
		BasicProperty(const TCHAR* name, size_t offset);
		/// @brief プロパティの値を取得する関数
		/// @param instane メンバ変数の場合はクラスのインスタンスが必要
		/// @return Tの値
		T GetValue(void* instane = nullptr);

		/// @brief プロパティの値をセットする関数
		/// @param instance メンバ変数の場合はクラスのインスタンスが必要
		/// @param value 
		/// @return 
		bool SetValue(T value,void* instance = nullptr);
	};
}

#include"detail/BasicProperty_impl.inl"