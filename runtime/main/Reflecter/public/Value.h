#pragma once
#include<type_traits>
#include<typeindex>
#include<bitset>
#include"detail/void_ptr.h"

namespace HARMONY
{
	enum class ValueKind
	{
		ARITHMETIC,
		SEQUENTIAL_ARRAY,
		ASSOCIATIVE_CONTAINER,
		WRAPPED,
		POINTER,
		STRING,
		MAX
	};

	struct ValueImpl
	{
		template<typename T>
		ValueImpl(T&& varPtr)
		:_index(typeid(T))
		{
			_ptr = DETAIL::get_void_ptr(varPtr);
		}
		void* _ptr;
		std::type_index _index;
		std::bitset<(size_t)ValueKind::MAX> _bit;
	};
	
	class REFLECTER_API Value
	{
	public:
		Value();
		template<typename T,
		typename Tp = std::remove_cv_t<std::remove_reference_t<T>>>
		typename std::enable_if_t<!std::is_same_v<T,Value>>
		Value(T& var);
		Value(const Value& other);
		Value(Value&& other);
		~Value();
		bool TestValueKind(ValueKind kind);
		template<typename T>
		T TryConvert();
	private:
		struct ValueImpl* _impl;
	};
}

#include"inl/Value.inl"