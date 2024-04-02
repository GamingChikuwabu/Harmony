#include"Property/ScriptArray.h"

namespace HARMONY
{
	size_t ScriptArray::GetSize()
	{
		return getSizeFunc(instance);
	}
	void* ScriptArray::GetData()
	{
		return getDataFunc(instance);
	}

	Class* ScriptArray::GetInnerClass()
	{
		return _innerClass;
	}
}