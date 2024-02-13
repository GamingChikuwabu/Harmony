#pragma once
#include"Types/type.h"
#include <any>
#include <type_traits>

namespace HARMONY
{
    class variant {
    public:
        // 汎用コンストラクタ
        template<typename T>
        variant(T&& arg) : _value(std::forward<T>(arg)) 
        {
            _type = Type::FindByType<T>();
        }

        // 汎用代入演算子
        template<typename T>
        variant& operator=(T&& arg) {

            _value = std::forward<T>(arg);
            _type = Type::FindByType<T>();
            return *this;
        }

        // 比較演算子の実装
        template<typename T>
        bool operator==(const T& arg) const {
            if (_value.type() == typeid(T)) {
                // std::any_castを使用して値を取得し、比較します
                return std::any_cast<T>(_value) == arg;
            }
            return false;
        }

    private:
        Type     _type;
        std::any _value; // 値を保持するためのメンバ 
    };
}