#pragma once

namespace HARMONY
{
    namespace DETAIL
    {
        struct member_object_pointer
        {};

        struct object_pointer
        {};

        struct as_pointer
        {};

        struct numeric
        {};
    }

    template<typename ACCESSTYP, typename GETPLICY, typename BASETYPE,typename ACCESSER>
    class  PropertyAccessor{};

    template<typename C,typename A,class PropertyBaseType>
    class  PropertyAccessor<DETAIL::member_object_pointer,DETAIL::numeric,PropertyBaseType,A (C::*)> : public PropertyBaseType
    {
        using Accesser = A (C::*);
        using Super = PropertyBaseType;
    private:
        Accesser memberPtr; 
    public:
        
        PropertyAccessor(Accesser ptr,const TCHAR* name)
        : memberPtr(ptr)
        ,Super(name){}

        A GetPropertyValue(void* instance)override
        {
            C* class_ = reinterpret_cast<C*>(instance);
            return class_->*memberPtr;
        }

        bool SetPropertyValue(void* instance, A value)override
        {
            C* class_ = reinterpret_cast<C*>(instance);
            class_->*memberPtr = value;
            return true;
        }
    };
}