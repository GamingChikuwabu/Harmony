#pragma once

namespace HARMONY
{
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