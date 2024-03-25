#pragma once
#include <cwchar>

namespace HARMONY
{
	class HMString
	{
    public:
        HMString() = default;
        HMString(const HMString&) = default;
        HMString(HMString&&) = default;

        // コンストラクタ
        HMString(const wchar_t* str = L"") {
            length = std::wcslen(str);
            data = new wchar_t[length + 1];
            std::wcscpy(data, str);
        }

        // デストラクタ
        ~HMString() {
            delete[] data;
        }

        // コピー構築子
        HMString(const HMString& other) {
            length = other.length;
            data = new wchar_t[length + 1];
            std::wcscpy(data, other.data);
        }

        // コピー代入演算子
        HMString& operator=(const HMString& other) {
            if (this != &other) {
                delete[] data;
                length = other.length;
                data = new wchar_t[length + 1];
                std::wcscpy(data, other.data);
            }
            return *this;
        }

        // +オペレータでの文字列の連結
        HMString operator+(const HMString& other) const {
            HMString newStr;
            newStr.length = length + other.length;
            newStr.data = new wchar_t[newStr.length + 1];
            std::wcscpy(newStr.data, data);
            std::wcscat(newStr.data, other.data);
            return newStr;
        }

        // ==オペレータでの等価比較
        bool operator==(const HMString& other) const {
            return std::wcscmp(data, other.data) == 0;
        }

        // !=オペレータでの非等価比較
        bool operator!=(const HMString& other) const {
            return !(*this == other);
        }

        // []オペレータでの添え字アクセス
        wchar_t& operator[](size_t index) {
            return data[index];
        }

        const wchar_t& operator[](size_t index) const {
            return data[index];
        }

        // 文字列を出力するメソッド
        void print() const {
            std::wcout << data << std::endl;
        }

        size_t Length() const {
            return length;
        }

    private:
        wchar_t* data; // 文字列データを保持する配列
        size_t length; // 文字列の長さ
    };
}