#pragma once
#include<string>
#include<any>
#include"Types/type.h"
#include"Archive/access.h"

namespace HARMONY
{
    namespace DETAIL {
        struct Property_Data; // 前方宣言
    }
    class TYPEMANAGER_API Property
    {
    public:
        Property() = default;

        const std::string GetName()const;

        void SetValue(void* classinstance, std::any value);

        std::any GetValue(void* classinstance);

        PROPERTY_ACCESS_LEVEL GetAccessLevel() const;

    private:
        DETAIL::Property_Data* _propertyData;
    };
}