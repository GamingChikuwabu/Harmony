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

    // メンバの型を抽出するメタ関数の定義
    template<typename MemberPtr>
    struct member_type;

    // メンバポインタに対するテンプレート特殊化
    template<typename ClassType, typename MemberType>
    struct member_type<MemberType ClassType::*> {
        using type = MemberType;
    };

    template<typename ACCESSTYP, typename GETPLICY, typename BASETYPE>
    class  PropertyAccessor{};

    template<typename C,typename A,class PropertyBaseType>
    class  PropertyAccessor<DETAIL::member_object_pointer,DETAIL::numeric,PropertyBaseType> : public PropertyBaseType
    {
        using MemberType = member_type<decltype()>
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