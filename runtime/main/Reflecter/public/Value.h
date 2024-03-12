#pragma once
#include<type_traits>
#include<memory>


namespace HARMONY
{
	enum class ValueKind;
	class REFLECTER_API Value
	{
	public:
		Value();
		template<typename T>
		Value(T&& var);
		Value(const Value& other);
		Value(Value&& other);
		~Value();
		bool TestValueKind(ValueKind kind);
		template<typename T>
		T TryConvert();
	private:
		std::shared_ptr<struct ValueImpl> _impl;
	};
}

#include"inl/Value.inl"