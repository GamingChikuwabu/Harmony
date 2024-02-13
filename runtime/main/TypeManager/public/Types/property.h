#pragma once
#include<string>
#include<any>
#include"Types/type.h"
#include"ItemCreater.h"
#include"Archive/access.h"

namespace HARMONY
{
    namespace DETAIL {
        struct Property_Data; // 前方宣言
        class ItemCreater;
    }
    class TYPEMANAGER_API Property
    {
    public:
        Property() = default;

        const std::string GetName()const;

        void* GetValue(void* classinstance);
        // 実際のセット処理を隠蔽するためのプライベートメンバ関数
        void SetValue(void* classinstance, const std::any& value);

        PROPERTY_ACCESS_LEVEL GetAccessLevel() const;
    private:
        friend DETAIL::ItemCreater;
        DETAIL::Property_Data* _data;
    };
}