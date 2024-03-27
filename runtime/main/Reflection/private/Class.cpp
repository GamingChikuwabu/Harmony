#include"Class.h"
#include"Property.h"
#include"Construction.h"
#include"gc/gc.h"

namespace HARMONY
{
	const HMArray<Property*>& Class::GetProperties() const
	{
		return _property;
	}

	void* Class::Create()
	{
		return _construction->invoke();
	}

	Class* Class::GetClassByName(const TCHAR* name)
	{
		for (auto cl : _allClass)
		{
			if (cl->_name == HMString(name))
			{
				return cl;
			}
		}
		return nullptr;
	}
}