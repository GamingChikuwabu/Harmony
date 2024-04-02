#pragma once
#include"PlatformString.h"
#include"gc/gc.h"

namespace HARMONY
{
    class HMStringImpl {
    public:
        TCHAR* data; // 文字列データを保持する配列
        size_t length; // 文字列の長さ

        HMStringImpl(const TCHAR* str = TEXT("")) {
            length = TSTRLEN(str);
            // GC_mallocを使用してメモリを確保
            data = static_cast<TCHAR*>(GC_malloc((length + 1) * sizeof(TCHAR)));
            TSTRCPY(data, str);
        }

        // コピーコンストラクタ
        HMStringImpl(const HMStringImpl& other) : length(other.length), data(nullptr) {
            if (other.data != nullptr) {
                // GC_mallocを使用してメモリを確保
                data = static_cast<TCHAR*>(GC_malloc((other.length + 1) * sizeof(TCHAR)));
                TSTRCPY(data, other.data);
            }
            else {
                // 空文字列を割り当てる
                data = static_cast<TCHAR*>(GC_malloc(sizeof(TCHAR)));
                data[0] = TEXT('\0');
            }
        }

        // デストラクタ
        ~HMStringImpl() {
            
        }

        // 他のメンバ関数（例: 文字列連結など）も同様に定義
    };
}