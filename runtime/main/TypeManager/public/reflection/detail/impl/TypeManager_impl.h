#include "TypeManager.h"
#pragma once
#include"detail/registration/registration.h"
#include"detail/property/property_wrapper_member_object.h"
#include"property.h"
#include"type.h"

namespace HARMONY
{
    template<class ClassType>
    inline TypeManager::class_<ClassType>::class_(std::string name)
    {
        auto t = type::Get<ClassType>();
        registration::RegisterCustomTypeName(t, name);
    }
    template<class ClassType>
    inline TypeManager::class_<ClassType>::~class_()
    {
       
    }
    template<class ClassType>
    template<typename ...Args>
    inline typename std::enable_if<std::is_constructible<ClassType, Args...>::value, TypeManager::class_<ClassType>&>::type TypeManager::class_<ClassType>::construct()
    {

        return *this;
    }
    template<class ClassType>
    template<typename A>
    inline auto HARMONY::TypeManager::class_<ClassType>::property(const std::string& name, A memberPtr)
        -> std::enable_if_t<std::is_member_pointer<A>::value, class_&>
    {
        auto t = type::Get<ClassType>();
        auto classData = t.GetData()->_getClassDataFunc();
        HARMONY::property prop = create_item<HARMONY::property>
            (
                new property_wrapper<member_object_ptr, A, void, access_level::PUBLIC, return_as_copy, set_value >(name, type::Get<ClassType>())
            );
        classData.m_properties.push_back(prop);
        return *this;
    }
    template<class ClassType>
    template<typename A>
    inline auto TypeManager::class_<ClassType>::property_readonry(const std::string& name, A memberPtr)
        -> std::enable_if_t<std::is_member_pointer<A>::value, class_&>
    {
        return *this;
    }
}