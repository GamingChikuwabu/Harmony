#pragma once
#include"PlatformSimdchacker.h"
#include"Macro/ObjectMacro.h"
#include"Vector3f.generate.h"

namespace HARMONY
{
    namespace MATH
    {
        HMCLASS()
        struct UTILITY_API Vector3f
        {
            HM_CLASS_BODY()
            union
            {
                __m128 simd; // SIMD型を使用
                struct
                {
                    HMPROPERTY()
                    float x;
                    HMPROPERTY() 
                    float y;
                    HMPROPERTY()
                    float z;
                };
            };

            // コンストラクタ
            Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

            // オペレータオーバーロード
            Vector3f operator+(const Vector3f& other) const;
            Vector3f operator-(const Vector3f& other) const;
            Vector3f operator*(float scalar) const;

            // 内積と外積
            static float dot(const Vector3f& a, const Vector3f& b);
            static Vector3f cross(const Vector3f& a, const Vector3f& b);

            // ベクトルの長さ
            float length() const;

        private:
            // __m128型からVector3fを生成するプライベートコンストラクタ
            Vector3f(__m128 simdVal) : simd(simdVal)
            {
                // __m128型の値からx, y, zを抽出
                _mm_store_ss(&x, simdVal);
                _mm_store_ss(&y, _mm_shuffle_ps(simdVal, simdVal, _MM_SHUFFLE(1, 1, 1, 1)));
                _mm_store_ss(&z, _mm_shuffle_ps(simdVal, simdVal, _MM_SHUFFLE(2, 2, 2, 2)));
            }
        };
    }
}