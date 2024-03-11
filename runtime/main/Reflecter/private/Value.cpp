#include"Value.h"


namespace HARMONY
{
	Value::Value()
	{

	}

	Value::Value(const Value& other)
	:_impl(other._impl)
	{

	}

	Value::Value(Value&& other)
	:_impl(other._impl)
	{

	}

	Value::~Value()
	{
		if (_impl)
		{
			delete _impl;
		}
	}


	bool Value::TestValueKind(ValueKind kind)
	{
		return false;
	}
}