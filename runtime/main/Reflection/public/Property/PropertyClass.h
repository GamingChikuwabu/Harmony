#pragma once
#include"Property.h"
#include<functional>

namespace HARMONY
{
	template<typename C>
	concept HasGetClass = requires(C * c) {
		{ c->GetClass() } -> std::convertible_to<void*>;
	};
	class REFLECTION_API PropertyClass : public Property
	{
	public:
		template<typename C,typename AC>
		requires HasGetClass<C>
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