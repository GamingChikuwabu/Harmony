#pragma once
#include"HMArray.h"
#include"HMString.h"

namespace HARMONY
{
	class Property;
	class Construction;
	class Class;
	struct ClassData
	{
		ClassData(const TCHAR* name, size_t size, const HMArray<Property*>& prop) :_name(name),_size(size),_property(prop) {

		}
		const TCHAR* _name;
		const size_t _size;
		const HMArray<Property*> _property;
		const HMArray<Class*> _derivedClass;
		const Class* _baseClass;
		const Construction* _construction;
	};
}