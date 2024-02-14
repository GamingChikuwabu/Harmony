#pragma once
#include<string>
#include<any>
#include"Types/type.h"
#include"Archive/access.h"

namespace HARMONY
{
    class variant;
    class instance;
    namespace DETAIL {
        struct Property_Data; // 前方宣言
        class ItemCreator;
    }

    class TYPEMANAGER_API Property
    {
    public:
        Property() {};
        const std::string GetName()const;

        variant GetValue(instance classinstance);
        
        void SetValue(instance classinstance, const std::any& value);

        ACCESS_LEVEL GetAccessLevel() const;
    private:
        Property(std::shared_ptr<DETAIL::Property_Data> data);
        friend DETAIL::ItemCreator;
        std::shared_ptr<DETAIL::Property_Data> _data;
    };
}