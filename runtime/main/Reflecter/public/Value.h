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
		std::shared_ptr<struct ValueImplBase> _impl;//前方宣言と参照カウント用に使用
	};
}

#include"inl/Value.inl"