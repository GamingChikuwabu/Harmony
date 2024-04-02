#include"Property/PropertyClass.h"
#pragma once
namespace HARMONY
{
    template<typename C, typename AC>
    requires IsDerivedFromHMObject<std::remove_pointer_t<AC>>
    PropertyClass::PropertyClass(const TCHAR* name, AC C::* memberptr)
    :PropertyClass::Property(name, nullptr, sizeof(std::remove_pointer_t<AC>)),_isPointer(true)
    {
        getter = [memberptr](void* instance) -> void* {
            C* classPtr = reinterpret_cast<C*>(instance);
            // メンバがポインタなので、そのまま返します。
            return &(classPtr->*memberptr);
            };

        setter = [memberptr](void* instance, void* value) -> bool {
            C* classPtr = reinterpret_cast<C*>(instance);
            // valueをAC型のポインタとして解釈し、値を設定します。
            classPtr->*memberptr = *static_cast<AC*>(value);
            return true;
            };

        classGetter = []() -> Class* {
            return std::remove_pointer_t<AC>::StaticGetClass();
            };
    }

    // GetClassメソッドを持つACに対するPropertyClassのコンストラクタ
    template<typename C, typename AC>
    requires HasGetClassMethod<AC>
    PropertyClass::PropertyClass(const TCHAR* name, AC C::* memberptr)
   :PropertyClass::Property(name, nullptr, sizeof(AC)), _isPointer(false)
   {
        getter = [memberptr](void* instance) -> void* {
            C* classPtr = reinterpret_cast<C*>(instance);
            // ACがポインタでない場合は、メンバのアドレスを返します。
            return &(classPtr->*memberptr);
            };

        setter = [memberptr](void* instance, void* value) -> bool {
            C* classPtr = reinterpret_cast<C*>(instance);
            // valueをAC型のポインタとして解釈し、値を設定します。
            classPtr->*memberptr = *static_cast<AC*>(value);
            return true;
            };

        classGetter = []() -> Class* {
            return AC::StaticGetClass();
        };
    }

	template<typename C>
	inline void* PropertyClass::GetValue(C* instance)
	{
		return getter(instance);
	}

	template<typename C>
	inline bool PropertyClass::SetValue(C* instance,void* value)
	{
		return setter(instance,value);
	}

	template<typename T, typename C>
	T* PropertyClass::Convert(C* instance)
	{
		return static_cast<T*>(getter(instance));
	}
}