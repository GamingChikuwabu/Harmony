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

        struct as_copy
        {};
    }

    template<typename ACCESSTYP, typename GETPLICY, typename A>
    class  PropertyAccessor {};

    template<typename C,typename A>
    class  PropertyAccessor<DETAIL::member_object_pointer,DETAIL::as_pointer,A C::*>
    {
    private:
        A C::* memberPtr; // Pointer to member of class C

    public:
        // Constructor saves the member pointer
        PropertyAccessor(A C::* ptr) : memberPtr(ptr) {}

        // Getter - returns a pointer to the member
        A* GetValue(C* obj) const
        {
            return obj->*memberPtr;
        }

        // Setter - sets the member value via a pointer
        void SetValue(C* obj, A* value) const
        {
            obj->*memberPtr = *value;
        }
    };

    template<typename C, typename A>
    class  PropertyAccessor<DETAIL::member_object_pointer, DETAIL::as_copy, A C::*>
    {
        
    };

    template<typename ACCESSTYP, typename GETPLICY, typename A>
    class  PropertyAccessor {};
    template<typename ACCESSTYP, typename GETPLICY, typename A>
    class  PropertyAccessor {};


    template<typename C, typename A>
    class  PropertyAccessor {
    public:
        using access = A C::*; // データメンバへのポインタを示す型エイリアス

        PropertyAccessor(access acc) : _acc(acc) {};

        // クラスのインスタンスから値を取得
        inline A GetValue(void* classInstance)const {
            C* Instance = reinterpret_cast<C*>(classInstance);
            return Instance->*_acc;
        }

        // クラスのインスタンスに値を設定
        inline bool SetValue(void* classInstance, A& value) {
            C* Instance = reinterpret_cast<C*>(classInstance);
            Instance->*_acc = value;
        }

    private:
        access _acc; // メンバ変数へのポインタ
    };
}