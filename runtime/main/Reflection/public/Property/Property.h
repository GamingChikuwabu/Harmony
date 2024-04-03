#pragma once
#include"HMString.h"
#include"PropertyKind.h"
#include<bitset>

// メンバーのオフセットを計算するマクロ
#define OFFSET_OF(ClassType, Member) \
    (reinterpret_cast<std::size_t>(&reinterpret_cast<ClassType*>(0)->Member))

namespace HARMONY
{
	class REFLECTION_API Property
	{
	public:
		/// @brief プロパティのコンストラクタ
		/// @param name プロパティの名前
		/// @param size プロパティのサイズ
		Property(
			const TCHAR* name
			,const TCHAR* elementName
			,size_t size
			,size_t align
			, PropertyKind kind);
		/// @brief デストラクタ
		~Property() = default;
		/// @brief プロパティの種類を返す関数
		/// @return プロパティの種類
		virtual PropertyKind GetKind() { return PropertyKind(); }
		/// @brief 名前を取得する
		/// @return メンバのプロパティのみ名前が得られます
		const TCHAR* GetPropertyName() { return _name; }
		/// @brief このプロパティの型の名前を取得する
		/// @return 型名
		const TCHAR* GetElementName() { return _elementName; }
		/// @brief プロパティのサイズ
		/// @return プロパティのサイズ
		size_t GetElementSize() { return _size; }
		/// @brief プロパティのアライメント
		/// @return アライメントのサイズ
		size_t GetElementAlign() { return _align; }
	private:
		const TCHAR* _name;
		const TCHAR* _elementName;
		size_t _size;
		size_t _align;
		std::bitset<static_cast<size_t>(PropertyKind::MAX)> _kind;
	};
}

//#include"detail/Property_impl.inl"