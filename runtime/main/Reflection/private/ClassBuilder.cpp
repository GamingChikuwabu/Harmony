#include"ClassBuilder.h"
#include"Class/Class.h"
#include<map>

namespace HARMONY
{
	void ClassBuilder::Registration(const TCHAR* name, Class* (*classCreateFunc)())
	{
		_classCreatorFunction[name] = classCreateFunc;
	}

	Class* ClassBuilder::GetClassByname(const TCHAR* name)
	{
		auto it = _classCreatorFunction.find(name);
		if (it != _classCreatorFunction.end())
		{
			Class* (*classCreateFunc)() = it->second;
			if (classCreateFunc) {
				return classCreateFunc();
			}
		}
		return nullptr;
	}
}