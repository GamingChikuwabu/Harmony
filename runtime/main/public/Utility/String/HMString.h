#pragma once
#include"PlatformString.h"

namespace HARMONY
{
	class UTILITY_API HMString
	{
    public:
        // コンストラクタとデストラクタ
        HMString();
        HMString(const TCHAR* str);
        HMString(const HMString& other);
        HMString(HMString&& other);
        ~HMString();

        HMString& operator=(const HMString& other);
        HMString operator+(const HMString& other) const;// +オペレータでの文字列の連結

        // ==オペレータでの等価比較
        bool operator==(const HMString& other) const;

        // !=オペレータでの非等価比較
        bool operator!=(const HMString& other) const;

        // []オペレータでの添え字アクセス
        TCHAR& operator[](size_t index);

        const TCHAR& operator[](size_t index) const;

        size_t Length() const;

        TCHAR* GetRaw()const;

    public:
        HMString& operator=(HMString&&) noexcept = default;
    private:
        class HMStringImpl* pImpl; // Pimplパターンの実装
    };
}