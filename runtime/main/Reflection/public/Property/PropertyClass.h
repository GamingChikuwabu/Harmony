#pragma once
#include"Property.h"
#include<functional>

namespace HARMONY
{
	class Class;
	class REFLECTION_API PropertyClass : public Property
	{
	public:
		template<typename C,typename AC>
		PropertyClass(const TCHAR* name, AC C::* memberptr);
		template<typename C>
		void* GetValue(C* instance);
		template<typename C>
		bool SetValue(C* instance,void* value);
		template<typename T, typename C>
		T* Convert(C* instance);
		inline Class* GetClass();
		inline PropertyKind GetKind()override;
	private:
		std::function<void* (void*)> getter;
		std::function<bool(void*, void*)> setter;
		std::function<Class* ()> classGetter;
	};
}

#include"Property/detail/PropertyClass.inl"