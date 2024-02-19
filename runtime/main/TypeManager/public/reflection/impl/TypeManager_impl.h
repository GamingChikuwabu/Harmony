#include"TypeManager.h"
#pragma once

namespace HARMONY
{
    template<class ClassType>
    inline TypeManager::class_<ClassType>::class_(std::string name)
    {
    }

    template<class ClassType>
    template<typename ...Args>
    inline typename std::enable_if<std::is_constructible<ClassType, Args...>::value,
        TypeManager::class_<ClassType>&>::type TypeManager::class_<ClassType>::construct()
    {
        return *this;
    }
    template<class ClassType>
    template<typename MemberType>
    inline auto TypeManager::class_<ClassType>::property(const std::string& name, MemberType ClassType::* memberPtr) -> std::enable_if_t<std::is_member_pointer<MemberType ClassType::*>::value, class_&>
    {
        return *this;
    }
}