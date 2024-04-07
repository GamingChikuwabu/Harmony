#pragma once
#include <cstring>

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

    template<typename ACCESSTYP, typename GETPLICY, typename BASETYPE>
    class PropertyAccessor{};

    template<class PropertyBaseType>
    class PropertyAccessor<DETAIL::member_object_pointer,DETAIL::numeric,PropertyBaseType> : public PropertyBaseType
    {
        using Super = PropertyBaseType;
    private:
        size_t memberOffset; 
    public:
        PropertyAccessor(size_t offset,const TCHAR* name)
        :Super(name),memberOffset(offset){}

        void* GetPropertyValue(void* instance) override {
            char* memberAddress = static_cast<char*>(instance) + memberOffset;
            return memberAddress;
        }

        bool SetPropertyValue(void* instance, void* value)override
        {
            // プロパティのサイズを取得
            size_t propertySize = this->GetElementSize();
            // インスタンスの指定されたメンバ位置を取得
            char* memberAddress = static_cast<char*>(instance) + memberOffset;
            // valueからメンバの位置へデータをコピー
            std::memcpy(memberAddress, value, propertySize);
            return true;
        }
    };

    template<class PropertyBaseType>
    class PropertyAccessor<DETAIL::object_pointer, DETAIL::numeric, PropertyBaseType> : public PropertyBaseType
    {
        using Super = PropertyBaseType;
    public:
        PropertyAccessor()
        :Super(TSTR("inner")) {}

        void* GetPropertyValue(void* instance) override {
            return instance;
        }

        bool SetPropertyValue(void* instance, void* value)override
        {
            std::memcpy(instance, value, this->GetElementSize());
            return true;
        }
    };

}