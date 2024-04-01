#include"Class.h"
#include"Property.h"
#include"Construction.h"
#include"gc/gc.h"
#include"Class/deteil/ClassData.h"

namespace HARMONY
{
	inline Class::Class(ClassData* data):_data(data)
	{

	}

	const TCHAR* Class::GetName()const
	{
		return _data->_name;
	}

	size_t Class::GetElementSize()const
	{
		return _data->_size;
	}

	const HMArray<Property*>& Class::GetProperties() const
	{
		return _data->_property;
	}

	void* Class::Create()
	{
		return _data->_construction->invoke();
	}

	Class* Class::GetBaseClass()
	{
		if (_data->_baseClass)
		{
			return _data->_baseClass();
		}
		return nullptr;
	}
}