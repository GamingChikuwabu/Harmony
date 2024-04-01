#pragma once
#include<type_traits>

namespace HARMONY
{
	enum class PropertyKind
	{
		Bool,
		Int32,
		Int64,
		Float,
		Double,
		String,
		Array,
		Map,
		Class,
		Object
	};

	class HMObject;

	// デフォルトのテンプレート構造体定義
	template<typename T, typename Enable = void>
	struct innerkind 
	{
		static_assert(std::is_same<T, void>::value, "HMArrayに許可されていない型です。");
	};

	// bool型に対する特殊化
	template<>
	struct innerkind<bool> {
		static const HARMONY::PropertyKind value = HARMONY::PropertyKind::Bool;
	};

	// int型に対する特殊化（すでに示されています）
	template<>
	struct innerkind<int32_t> {
		static const HARMONY::PropertyKind value = HARMONY::PropertyKind::Int32;
	};

	// その他の型に対する特殊化
	template<>
	struct innerkind<int64_t> {
		static const HARMONY::PropertyKind value = HARMONY::PropertyKind::Int64;
	};

	template<>
	struct innerkind<float> {
		static const HARMONY::PropertyKind value = HARMONY::PropertyKind::Float;
	};

	template<>
	struct innerkind<double> {
		static const HARMONY::PropertyKind value = HARMONY::PropertyKind::Double;
	};

	template<>
	struct innerkind<HARMONY::HMString> {
		static const HARMONY::PropertyKind value = HARMONY::PropertyKind::String;
	};

	// TがHMObjectから派生しているクラスの場合
	template<typename T>
	struct innerkind<T, std::enable_if_t<std::is_base_of<HMObject, std::remove_pointer_t<T>>::value>> {
		static const HARMONY::PropertyKind value = HARMONY::PropertyKind::Object;
	};

	// TがHMObjectから派生していないクラスの場合
	template<typename T>
	struct innerkind<T, std::enable_if_t<!std::is_base_of<HMObject, std::remove_pointer_t<T>>::value>> {
		// コンパイル時にエラーを発生させる
		static_assert(std::is_base_of<HMObject, std::remove_pointer_t<T>>::value, "TはHMObjectを継承した型でなければなりません。");
	};
}