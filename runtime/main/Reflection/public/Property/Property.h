#pragma once
#include"HMString.h"
#include"PropertyKind.h"
#include"Class/Class.h"
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

	template<typename T>
	class PropertyNumeric:public Property
	{
		using Super = Property;
	public:
		PropertyNumeric(
			const TCHAR* name,
			const TCHAR* elementName,
			PropertyKind kind) :
			Super(name, elementName, sizeof(T), alignof(T), kind) {};
		
		virtual T GetPropertyValue(void* instance);

		virtual bool SetPropertyValue(void* instance,T value);
	};

	template<typename T,typename Array>
	class PropertyArrayBase : public Property
	{
		using Super = Property;
	public:
		PropertyArrayBase(
			const TCHAR* name,
			const TCHAR* elementName
			) :
			Super(name, elementName, sizeof(Array<T>), alignof(Array<T>), PropertyKind::Array) {};

		size_t GetInnerElementSize() { return sizeof(T); }

		Property* GetInnerProperty() { return inner; }

	private:
		Property* inner;
	};

	template<typename T>
	class PropertyClassBase : public Property
	{
		using Super = Property;
	public:
		Class* GetClass() {return T::StaticGetClass();}

	};

	//================================================================================
	// bool Property
	//================================================================================
	class PropertyBool : public PropertyNumeric<bool>
	{
		using Super = PropertyNumeric<bool>;
	public:
		PropertyBool(
			const TCHAR* name)
			:Super(name, TEXT("bool"), PropertyKind::Bool) {};
	};

	//================================================================================
	// int Property
	//================================================================================

	class PropertyInt32 : public PropertyNumeric<int32_t>
	{
		using Super = PropertyNumeric<int32_t>;
	public:
		PropertyInt32(
			const TCHAR* name)
			:Super(name, TEXT("int32_t"), PropertyKind::Int32) {};
	};

	class PropertyUInt32 : public PropertyNumeric<uint32_t>
	{
		using Super = PropertyNumeric<uint32_t>;
	public:
		PropertyUInt32(
			const TCHAR* name)
			:Super(name, TEXT("uint32_t"), PropertyKind::UInt32) {};
	};

	class PropertyInt64 : public PropertyNumeric<int64_t>
	{
		using Super = PropertyNumeric<int64_t>;
	public:
		PropertyInt64(
			const TCHAR* name)
			:Super(name, TEXT("int64_t"), PropertyKind::Int64) {};
	};

	class PropertyUInt64 : public PropertyNumeric<uint64_t>
	{
		using Super = PropertyNumeric<uint64_t>;
	public:
		PropertyUInt64(
			const TCHAR* name)
			:Super(name, TEXT("uint64_t"), PropertyKind::UInt64) {};
	};

	//================================================================================
	// Floating Property
	//================================================================================

	class PropertyFloat : public PropertyNumeric<float>
	{
		using Super = PropertyNumeric<float>;
	public:
		PropertyFloat(
			const TCHAR* name)
			:Super(name, TEXT("float"), PropertyKind::Float) {};
	};

	class PropertyDouble : public PropertyNumeric<double>
	{
		using Super = PropertyNumeric<double>;
	public:
		PropertyDouble(
			const TCHAR* name)
			:Super(name, TEXT("double"), PropertyKind::Double) {};
	};

	//================================================================================
	// String Property
	//================================================================================

	class PropertyString : public PropertyNumeric<HMString>
	{
		using Super = PropertyNumeric<HMString>;
	public:
		PropertyString(
			const TCHAR* name)
			:Super(name, TEXT("HMString"), PropertyKind::String) {};
	};
}