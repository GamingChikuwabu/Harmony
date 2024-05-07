#pragma once
#include"PlatformSimdchacker.h"
#include"Macro/ObjectMacro.h"
#include"Macro/ManualRegisterMacro.h"

namespace HARMONY
{
    class Class;
    namespace MATH
    {
        HMCLASS()
        struct UTILITY_API Vector4f
        {
            HM_MANUAL_REGISTER_BASE_CLASS_BODY(Vector4f)
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
                    HMPROPERTY()
                        float w;
                };
            };
            Vector4f();
            Vector4f(float x, float y, float z, float w);
            Vector4f(const Vector4f& v);
            Vector4f(const __m128& v);
            Vector4f operator+(const Vector4f& v) const;
            Vector4f operator-(const Vector4f& v) const;
            Vector4f operator*(const Vector4f& v) const;
            Vector4f operator/(const Vector4f& v) const;
            Vector4f operator+(float v) const;
            Vector4f operator-(float v) const;
            Vector4f operator*(float v) const;
            Vector4f operator/(float v) const;
            Vector4f& operator=(const Vector4f& v);
            Vector4f& operator+=(const Vector4f& v);
            Vector4f& operator-=(const Vector4f& v);
            bool operator==(const Vector4f& v) const;
            bool operator!=(const Vector4f& v) const;
            float Dot(const Vector4f& v) const;
            Vector4f Cross(const Vector4f& v) const;
            float Magnitude() const;
            Vector4f Normalize() const;
            Vector4f Lerp(const Vector4f& v, float t) const;
            float Distance(const Vector4f& v) const;
            static Vector4f Lerp(const Vector4f& a, const Vector4f& b, float t);
            static float Distance(const Vector4f& a, const Vector4f& b);
            static float Dot(const Vector4f& a, const Vector4f& b);
            static Vector4f Cross(const Vector4f& a, const Vector4f& b);
            static Vector4f Normalize(const Vector4f& v);
            static Vector4f Zero();
            static Vector4f One();
            static Vector4f Up();
            static Vector4f Down();
            static Vector4f Right();
            static Vector4f Left();
            static Vector4f Forward();
            static Vector4f Backward();
        };
    }
}