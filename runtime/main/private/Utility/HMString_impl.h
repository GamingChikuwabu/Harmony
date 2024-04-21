#pragma once
#include"PlatformString.h"
#include"gc/gc.h"
#include<new>



namespace HARMONY
{
    class HMStringImpl {
    public:
        TCHAR* data; // 文字列データを保持する配列
        size_t length; // 文字列の長さ

        HMStringImpl(const TCHAR* str = TSTR("")) {
            length = TSTRLEN(str);
            // GC_mallocを使用してメモリを確保
            data = static_cast<TCHAR*>(GC_MALLOC((length + 1) * sizeof(TCHAR)));
            TSTRCPY(data, str);
        }

        // コピーコンストラクタ
        HMStringImpl(const HMStringImpl& other) : length(other.length), data(nullptr) {
            if (other.data != nullptr) {
                // GC_mallocを使用してメモリを確保
                data = static_cast<TCHAR*>(GC_MALLOC((other.length + 1) * sizeof(TCHAR)));
                TSTRCPY(data, other.data);
            }
            else {
                // 空文字列を割り当てる
                data = static_cast<TCHAR*>(GC_MALLOC(sizeof(TCHAR)));
                data[0] = TSTR('\0');
            }
        }

        // デストラクタ
        ~HMStringImpl() {
            
        }

        // 他のメンバ関数（例: 文字列連結など）も同様に定義
    };
}