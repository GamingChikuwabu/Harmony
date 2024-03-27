#pragma once
namespace HARMONY
{
    template <typename T1, typename T2>
    class HMPair {
    public:
        T1 first;
        T2 second;

        // デフォルトコンストラクタ
        HMPair() : first(T1()), second(T2()) {}

        // パラメータ付きコンストラクタ
        HMPair(const T1& first, const T2& second) : first(first), second(second) {}

        // 比較演算子のオーバーロード
        bool operator==(const HMPair& other) const {
            return first == other.first && second == other.second;
        }

        bool operator!=(const HMPair& other) const {
            return !(*this == other);
        }
    };
}