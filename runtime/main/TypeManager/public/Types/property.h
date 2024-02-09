#pragma once
#include<string>
#include<any>
#include"Types/type.h"
#include"Archive/access.h"

namespace HARMONY
{
    class TYPEMANAGER_API Property
    {
    public:
        /// @brief このプロパティが有効かどうか
        /// @return 有効時　True
        bool IsAalid() noexcept;


    };


    class PropertyBase {
    public:
        PropertyBase() {}
        virtual ~PropertyBase() {}

        virtual std::string GetName() const = 0;
        virtual void SetValue(void* object, std::any value) = 0;
        virtual std::any GetValue(void* object) const = 0;
    };

    template<typename ClassType, typename MemberType>
    class Property : public PropertyBase {
    public:
        Property(std::string name, MemberType ClassType::* memberPtr)
            : _name(std::move(name)), _memberPtr(memberPtr) {}

        std::string GetName() const override {
            return _name;
        }

        void SetValue(void* object, std::any value) override {
            ClassType* typedObject = static_cast<ClassType*>(object);
            if (typedObject && value.has_value() && value.type() == typeid(MemberType)) {
                // std::any_castを使用してvalueからMemberTypeへの安全なキャストを行う
                *typedObject.*_memberPtr = std::any_cast<MemberType>(value);
            }
        }

        std::any GetValue(void* object) const override {
            const ClassType* typedObject = static_cast<const ClassType*>(object);
            if (typedObject) {
                return std::any{ typedObject->*_memberPtr };
            }
            return {}; // 空のstd::anyを返す
        }

    private:
        std::string _name;
        MemberType ClassType::* _memberPtr;
    };
}