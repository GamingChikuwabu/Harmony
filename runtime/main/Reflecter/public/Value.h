#pragma once
#include<type_traits>

namespace HARMONY
{
	enum class ValueKind
	{
		ARITHMETIC,
		SEQUENTIAL_ARRAY,
		ASSOCIATIVE_CONTAINER,
		WRAPPED,
		POINTER,
		MAX
	};
	class Value
	{
	public:
		Value();
		template<typename T,typename Tp = std::remove_cv_t<std::remove_reference_t<T>>>
		Value(T&& var);
		bool TestValueKind(ValueKind kind);
		template<typename T>
		T TryConvert();
	private:
		struct ValueImpl* _impl;
	};
}

#include"inl/Value.inl"