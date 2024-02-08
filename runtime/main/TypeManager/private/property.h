#pragma once
#include<string>
#include"type.h"

namespace HARMONY
{
    template<typename ClassType, typename MemberType>
    class Property {
    public:
        Property(std::string name, MemberType ClassType::* memberPtr)
            : _name(name), _memberPtr(memberPtr), _type(typeid(MemberType)) {}

        // メンバ変数の名前を取得
        std::string GetName() const {
            return _name;
        }

        // メンバ変数の値を取得
        MemberType GetValue(const ClassType& object) const {
            return object.*_memberPtr;
        }

        // メンバ変数の値を設定
        void SetValue(ClassType& object, MemberType value) const {
            object.*_memberPtr = value;
        }

        const TypeBase& GetType() {
            return _type;
        }

    private:
        std::string _name;                  //プロパティの名前
        TypeBase        _type;                  //プロパティの型名
        MemberType ClassType::* _memberPtr; //メンバポインタ
    };
}