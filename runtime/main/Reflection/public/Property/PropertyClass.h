#pragma once
#include"Property.h"
#include<functional>
#include <concepts>
#include<type_traits>

namespace HARMONY
{
	class Class;
	template<typename T>
	concept IsDerivedFromHMObject = std::is_base_of_v<HMObject, T>;

	template<typename T>
	concept HasGetClassMethod = requires(T t) {
		{ t.GetClass() } -> std::convertible_to<Class*>;
	};

	class REFLECTION_API PropertyClass : public Property
	{
	public:
		template<typename C,typename AC>
		requires IsDerivedFromHMObject<std::remove_pointer_t<AC>>
		PropertyClass(const TCHAR* name, AC C::* memberptr);

		template<typename C, typename AC>
		requires HasGetClassMethod<AC>
		PropertyClass(const TCHAR * name, AC C::* memberptr);

		template<typename C>
		void* GetValue(C* instance);

		template<typename C>
		bool SetValue(C* instance,void* value);

		template<typename T, typename C>
		T* Convert(C* instance);

		inline Class* GetClass();

		inline PropertyKind GetKind()override;

		bool IsPointer() { return _isPointer; }
	private:
		std::function<void* (void*)> getter;
		std::function<bool(void*, void*)> setter;
		std::function<Class* ()> classGetter;
		const bool _isPointer;
	};
}

#include"Property/detail/PropertyClass.inl"