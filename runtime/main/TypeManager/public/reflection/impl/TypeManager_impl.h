#include "TypeManager.h"
#pragma once
#include"class_data.h"

namespace HARMONY
{
    template<class ClassType>
    inline TypeManager::class_<ClassType>::class_(std::string name)
    {
        _data = new DETAIL::class_data(); 
    }
    template<class ClassType>
    inline TypeManager::class_<ClassType>::~class_()
    {
        _classData[_data->_name] = *_data;
        delete _data;
    }
    template<class ClassType>
    template<typename ...Args>
    inline typename std::enable_if<std::is_constructible<ClassType, Args...>::value, TypeManager::class_<ClassType>&>::type TypeManager::class_<ClassType>::construct()
    {
        return *this;
    }
    template<class ClassType>
    template<typename MemberType>
    inline auto HARMONY::TypeManager::class_<ClassType>::property(const std::string& name, MemberType ClassType::* memberPtr) -> std::enable_if_t<std::is_member_pointer<MemberType ClassType::*>::value, class_&>
    {
        return *this;
    }
}