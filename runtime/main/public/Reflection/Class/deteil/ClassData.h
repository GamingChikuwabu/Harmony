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
		using BaseClassGetterFunc = Class * (*)();
		ClassData(
			const TCHAR* name,
			size_t size,
			const HMArray<Property*>& prop,
			BaseClassGetterFunc baseClassGetter = nullptr
		) :_name(name),
			_size(size),
			_property(prop),
			_baseClass(baseClassGetter){}

		const TCHAR* _name;
		const size_t _size;
		const HMArray<Property*> _property;
		const HMArray<Class*> _derivedClass;
		const BaseClassGetterFunc _baseClass;
		const Construction* _construction;
	};
}