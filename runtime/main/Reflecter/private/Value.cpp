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
		
	}


	bool Value::TestValueKind(ValueKind kind)
	{
		return false;
	}
}