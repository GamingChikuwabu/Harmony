#include"Value.h"
#include<typeindex>
#include<bitset>

namespace HARMONY
{
	struct ValueImpl
	{
		template<typename T>
		ValueImpl(void* varPtr)
		:_index(typeid(T))
		{
			_ptr = varPtr;
		}
		void* _ptr;
		std::type_index _index;
		std::bitset<(size_t)ValueKind::MAX> _bit;
	};


	Value::Value()
	{
	}

	bool Value::TestValueKind(ValueKind kind)
	{
		return false;
	}
}