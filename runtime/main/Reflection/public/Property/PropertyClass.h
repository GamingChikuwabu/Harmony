#pragma once
#include"Property.h"
#include<functional>

namespace HARMONY
{
	class REFLECTION_API PropertyClass : public Property
	{
	public:
		template<typename C,typename AC>
		PropertyClass(const TCHAR* name, AC C::* memberptr);
		template<typename C>
		void* GetValue(C* instance);
		template<typename C>
		bool SetValue(C* instance,void* value);
	private:
		std::function<void* (void*)> getter;
		std::function<bool(void*, void*)> setter;
	};
}

#include"Property/detail/PropertyClass.inl"