#pragma once
#include"Utility/String/HMString.h"
#include"PropertyKind.h"
#include"Reflection/Class/Class.h"
#include"HMObject.h"
#include<bitset>
#include<new>
#include <type_traits>

template<typename T>
concept HasGetClass = requires(T t) {
	{ t.GetClass() } -> std::convertible_to<class HARMONY::Class*>;
};

// メンバーのオフセットを計算するマクロ
#define OFFSET_OF(ClassType, Member) \
    (reinterpret_cast<std::size_t>(&reinterpret_cast<ClassType*>(0)->Member))

namespace HARMONY
{
	class UTILITY_API Property
	{
	public:
		/// @brief プロパティのコンストラクタ
		/// @param name プロパティの名前
		/// @param size プロパティのサイズ
		Property(
			const TCHAR* name
			, const TCHAR* elementName
			, size_t size
			, size_t align
			, PropertyKind kind) :_name(name), _elementName(elementName), _size(size), _align(align), _kind(kind) {};
		/// @brief デストラクタ
		~Property() = default;
		/// @brief プロパティの種類を返す関数
		/// @return プロパティの種類
		PropertyKind GetKind()const { return _kind; }
		/// @brief 名前を取得する
		/// @return メンバのプロパティのみ名前が得られます
		const TCHAR* GetPropertyName()const { return _name; }
		/// @brief このプロパティの型の名前を取得する
		/// @return 型名
		const TCHAR* GetElementName()const { return _elementName; }
		/// @brief プロパティのサイズ
		/// @return プロパティのサイズ
		size_t GetElementSize()const { return _size; }
		/// @brief プロパティのアライメント
		/// @return アライメントのサイズ
		size_t GetElementAlign()const { return _align; }
	
		virtual void* GetPropertyValue(void* instance) { return nullptr; }
		virtual bool SetPropertyValue(void*& instance, void* value) { return false; }
		template<typename T>
		void SetPropertyValue(void*& instance, T value)
		{
			T temp = value;
			if (instance)
			{
				void* memberPtr = GetPropertyValue(instance);
				std::memcpy(memberPtr, &temp, _size);
			}
		}
	private:
		const TCHAR* _name;
		const TCHAR* _elementName;
		size_t _size;
		size_t _align;
		PropertyKind _kind;
	};

	class UTILITY_API PropertyClass : public Property
	{
		using Super = Property;
	public:
		PropertyClass(
			const TCHAR* name,
			const TCHAR* elementName,
			size_t size,
			size_t align
		) :Super(name, elementName, size, align, PropertyKind::Class) {}

		PropertyClass(
			const TCHAR* name,
			const TCHAR* elementName,
			size_t size,
			size_t align,
			PropertyKind kind
		) :Super(name, elementName, size, align, kind) {}

		virtual	Class* GetPropertyClass() { return nullptr; };
	};

	template<typename T>
	class PropertyClassBase : public PropertyClass
	{
		using Super = PropertyClass;
	public:
		PropertyClassBase(
			const TCHAR* name)
			:Super(name, T::StaticGetClass()->GetName(), sizeof(T), alignof(T)) {};

		Class* GetPropertyClass()override { return T::StaticGetClass(); }
	};

	class HMObject;
	class PropertyObject :public PropertyClass
	{
		using Super = PropertyClass;
	public:
		PropertyObject(
			const TCHAR* name,
			const TCHAR* elementName,
			size_t size,
			size_t align
		):Super(name,elementName,size,align,PropertyKind::Object){}
		virtual Class* GetPropertyClassPolymorphic(HMObject* instance) { return nullptr; }
	};

	template<typename T, typename Tp = std::remove_pointer_t<T>>
	class PropertyObjectBase : public PropertyObject
	{
		using Super = PropertyObject;
	public:
		PropertyObjectBase(const TCHAR* name)
		:Super(name,Tp::StaticGetClass()->GetName(), sizeof(T), alignof(T)) {};
		Class* GetPropertyClassPolymorphic(HMObject* instance)override
		{
			return instance->GetClass();
		}
		Class* GetPropertyClass()override
		{
			return Tp::StaticGetClass();
		}
	};

	template<typename ACCESSTYP, typename GETPLICY, typename BASETYPE>
	class PropertyAccessor;

	template<typename T, typename Enable = void>
	struct innerkind
	{
		static_assert(std::is_same<T, void>::value, "HMArrayに許可されていない型です。");
	};

	template<>
	struct innerkind<int32_t> {
		using type = HARMONY::PropertyAccessor<HARMONY::DETAIL::object_pointer, HARMONY::DETAIL::numeric, class PropertyInt32>;
	};

	template<>
	struct innerkind<uint32_t> {
		using type = HARMONY::PropertyAccessor<HARMONY::DETAIL::object_pointer, HARMONY::DETAIL::numeric, class PropertyUInt32>;
	};

	// int64_t型の特殊化
	template<>
	struct innerkind<int64_t> {
		using type = HARMONY::PropertyAccessor<HARMONY::DETAIL::object_pointer, HARMONY::DETAIL::numeric, class PropertyInt64>;
	};

	// int64_t型の特殊化
	template<>
	struct innerkind<uint64_t> {
		using type = HARMONY::PropertyAccessor<HARMONY::DETAIL::object_pointer, HARMONY::DETAIL::numeric, class PropertyUInt64>;
	};

	// float型の特殊化
	template<>
	struct innerkind<float> {
		using type = HARMONY::PropertyAccessor<HARMONY::DETAIL::object_pointer, HARMONY::DETAIL::numeric, class PropertyFloat>;
	};

	// double型の特殊化
	template<>
	struct innerkind<double> {
		using type = HARMONY::PropertyAccessor<HARMONY::DETAIL::object_pointer, HARMONY::DETAIL::numeric, class PropertyDouble>;
	};

	template<>
	struct innerkind<HMString>
	{
		using type = HARMONY::PropertyAccessor<HARMONY::DETAIL::object_pointer, HARMONY::DETAIL::numeric, class PropertyString>;
	};

	template<typename T>
	requires HasGetClass<T>
	struct innerkind<T>
	{
		using type = HARMONY::PropertyAccessor<HARMONY::DETAIL::object_pointer, HARMONY::DETAIL::numeric, class PropertyClassBase<T>>;
	};

	template<typename T>
	requires std::is_pointer_v<T>
	struct innerkind<T>
	{
		using type = HARMONY::PropertyAccessor<HARMONY::DETAIL::object_pointer, HARMONY::DETAIL::numeric, class PropertyObjectBase<T>>;
	};

	class PropertyArray : public Property
	{
		using Super = Property;
	public:
		Property* inner;
		PropertyArray(
			const TCHAR* name,
			const TCHAR* elementName,
			size_t size,
			size_t align,
			Property* propertyPtr) :
			Super(name, elementName, size, align, PropertyKind::Array), inner(propertyPtr) {}
		virtual void* GetData(void* arrayInstance) { return nullptr; }
		virtual size_t GetArraySize(void* Instance) { return 0; }
		virtual void SetSize(size_t size, void* instance) {};
	};


	template<typename T>
	class PropertyArrayBase : public PropertyArray
	{
		using Super = PropertyArray;
		using Array = HMArray<T>;
	public:
		using InnerPropertyType = innerkind<T>::type;
		PropertyArrayBase(
			const TCHAR* name
		) :
		Super(name, TSTR("HMArray"), sizeof(Array), alignof(Array), static_cast<Property*>(new (GC_NEW(InnerPropertyType)) InnerPropertyType())) {};

		void* GetData(void* Instance)
		{
			Array* arrayData = reinterpret_cast<Array*>(GetPropertyValue(Instance));
			return arrayData->GetData();
		}

		size_t GetArraySize(void* Instance)
		{
			Array* arrayData = reinterpret_cast<Array*>(GetPropertyValue(Instance));
			return arrayData->GetSize();
		}

		void SetSize(size_t size, void* instance)
		{
			Array* array = reinterpret_cast<Array*>(GetPropertyValue(instance));
			array->ReSize(size);
		}
	};

	class PropertyPair : public Property
	{
		using Super = Property;
	};

	template<typename N,typename M>
	class PropertyPairBase : public PropertyPair
	{
		using Super = PropertyPair;
		using Pair = HMPair<N, M>;
	public:

	};

	class PropertyUMap : public Property
	{
		using Super = Property;
	public:
		Property* _pKey;
		Property* _pValue;
		PropertyUMap(
			const TCHAR* name,
			const TCHAR* elementName,
			size_t size,
			size_t align,
			Property* propertyKey,
			Property* propertyValue
		):Super(name, elementName, size, align, PropertyKind::UMap), _pKey(propertyKey), _pValue(propertyValue){}
		virtual HMArray<void*> GetPair(void* mapInstance) {	return HMArray<void*>();};
		virtual void* GetKey(void* pair) { return nullptr; }
		virtual void* GetValue(void* pair) { return nullptr; }
		virtual size_t GetSize(void* mapInstance) { return 0; }
		virtual void SetPair(void* instance, void* Key, void* value){/*継承先で実装*/};
	};

	template<typename Key,typename Value>
	class PropertyUMapBase : public PropertyUMap
	{
		using InnerPropertyTypeKey = innerkind<Key>::type;
		using InnerPropertyTypeValue = innerkind<Value>::type;
		using Super = PropertyUMap;
		using MAP = HMUnorderedMap<Key, Value>;
		using Itereter = MAP::iterator;
	public:
		PropertyUMapBase(const TCHAR* name)
			:Super(name, TSTR("HMUnorderedMap"), sizeof(MAP), alignof(MAP),
				static_cast<Property*>(new (GC_NEW(InnerPropertyTypeKey)) InnerPropertyTypeKey()),
				static_cast<Property*>(new (GC_NEW(InnerPropertyTypeValue)) InnerPropertyTypeValue())) {}

		HMArray<void*> GetPair(void* mapInstance)
		{
			HMArray<void*> pair;
			MAP map = *reinterpret_cast<MAP*>(mapInstance);
			for (const auto& mapMember : map)
			{
				// const修飾を取り除き、void*への変換を行う
				void* ptr = const_cast<void*>(static_cast<const void*>(&mapMember));
				pair.Add(static_cast<void*>(ptr));
			}
			return pair;
		}

		void SetPair(void* instance, void* _Key, void* _value)
		{
			MAP* map = reinterpret_cast<MAP*>(instance);
			Key innerKey = *reinterpret_cast<Key*>(_Key);
			Value innerValue = *reinterpret_cast<Value*>(_value);
			map->insert(innerKey,innerValue);
		}

		void* GetKey(void* pair)
		{
			HMPair<Key, Value>* _pair = reinterpret_cast<HMPair<Key, Value>*>(pair);
			return &_pair->first;
		}

		void* GetValue(void* pair)
		{
			HMPair<Key, Value>* _pair = reinterpret_cast<HMPair<Key, Value>*>(pair);
			return &_pair->second;
		}

		size_t GetSize(void* mapInstance)
		{
			MAP* map = reinterpret_cast<MAP*>(mapInstance);
			return map->size();
		}
	};

	template<typename T>
	class UTILITY_API PropertyNumeric:public Property
	{
		using Super = Property;
	public:
		PropertyNumeric(
			const TCHAR* name,
			const TCHAR* elementName,
			PropertyKind kind) :
			Super(name, elementName, sizeof(T), alignof(T), kind) {};

		bool GetBool(void* instance) {
			return *static_cast<bool*>(GetPropertyValue(instance));
		}

		int32_t GetInt32(void* instance)
		{
			return *static_cast<int32_t*>(GetPropertyValue(instance));
		}

		float GetFloat(void* instance) {
			return *static_cast<float*>(GetPropertyValue(instance));
		}

		double GetDouble(void* instance) {
			return *static_cast<double*>(GetPropertyValue(instance));
		}

		HMString GetString(void* instance) {
			return *static_cast<HMString*>(GetPropertyValue(instance));
		}

		int64_t GetInt64(void* instance) {
			return *static_cast<int64_t*>(GetPropertyValue(instance));
		}

		uint32_t GetUInt32(void* instance) {
			return *static_cast<uint32_t*>(GetPropertyValue(instance));
		}

		uint64_t GetUInt64(void* instance) {
			return *static_cast<uint64_t*>(GetPropertyValue(instance));
		}

		bool SetPropertyValue(void* instance,T value)
		{
			return SetPropertyValue(instance, static_cast<void*>(&value));
		}
	};

	
	

	//================================================================================
	// bool Property
	//================================================================================
	class UTILITY_API PropertyBool : public PropertyNumeric<bool>
	{
		using Super = PropertyNumeric<bool>;
	public:
		PropertyBool(
			const TCHAR* name)
			:Super(name, TSTR("bool"), PropertyKind::Bool) {};
	};

	//================================================================================
	// int Property
	//================================================================================

	class UTILITY_API PropertyInt32 : public PropertyNumeric<int32_t>
	{
		using Super = PropertyNumeric<int32_t>;
	public:
		PropertyInt32(
			const TCHAR* name)
			:Super(name, TSTR("int32_t"), PropertyKind::Int32) {};
	};

	class UTILITY_API PropertyUInt32 : public PropertyNumeric<uint32_t>
	{
		using Super = PropertyNumeric<uint32_t>;
	public:
		PropertyUInt32(
			const TCHAR* name)
			:Super(name, TSTR("uint32_t"), PropertyKind::UInt32) {};
	};

	class UTILITY_API PropertyInt64 : public PropertyNumeric<int64_t>
	{
		using Super = PropertyNumeric<int64_t>;
	public:
		PropertyInt64(
			const TCHAR* name)
			:Super(name, TSTR("int64_t"), PropertyKind::Int64) {};
	};

	class UTILITY_API PropertyUInt64 : public PropertyNumeric<uint64_t>
	{
		using Super = PropertyNumeric<uint64_t>;
	public:
		PropertyUInt64(
			const TCHAR* name)
			:Super(name, TSTR("uint64_t"), PropertyKind::UInt64) {};
	};

	//================================================================================
	// Floating Property
	//================================================================================

	class UTILITY_API PropertyFloat : public PropertyNumeric<float>
	{
		using Super = PropertyNumeric<float>;
	public:
		PropertyFloat(
			const TCHAR* name)
			:Super(name, TSTR("float"), PropertyKind::Float) {};
	};

	class UTILITY_API PropertyDouble : public PropertyNumeric<double>
	{
		using Super = PropertyNumeric<double>;
	public:
		PropertyDouble(
			const TCHAR* name)
			:Super(name, TSTR("double"), PropertyKind::Double) {};
	};

	//================================================================================
	// String Property
	//================================================================================

	class UTILITY_API PropertyString : public PropertyNumeric<HMString>
	{
		using Super = PropertyNumeric<HMString>;
	public:
		PropertyString(
			const TCHAR* name)
			:Super(name, TSTR("HMString"), PropertyKind::String) {};
	};
}