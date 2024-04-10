#pragma once
#include<cmath>
#include"PlatformSimdchacker.h"
#include"Vector3f.h"
#include"Macro/ObjectMacro.h"

namespace HARMONY
{
    namespace MATH
    {
        HMCLASS()
        struct UTILITY_API Quaternion
        {
            HM_MANUAL_REGISTER_BASE_CLASS_BODY(Quaternion)
            union
            {
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
                __m128 simd; // SIMD型を使用
            };
            Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : x(x), y(y), z(z), w(w) {};
            // 正規化
            void normalize() {
                float norm = sqrt(x * x + y * y + z * z + w * w);
                if (norm > 0.0f) {
                    float invNorm = 1.0f / norm;
                    x *= invNorm;
                    y *= invNorm;
                    z *= invNorm;
                    w *= invNorm;
                }
            }

            // 逆クォータニオン
            Quaternion inverse() const {
                return Quaternion(-x, -y, -z, w);
            }

            // クォータニオンの乗算
            Quaternion operator*(const Quaternion& rhs) const {
                return Quaternion(
                    w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
                    w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x,
                    w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w,
                    w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z
                );
            }

            // ベクトルとの乗算（回転）
            Vector3f rotate(const Vector3f& v) const {
                Quaternion vecQuat(v.x, v.y, v.z, 0.0f);
                Quaternion resQuat = (*this) * vecQuat * this->inverse();
                return Vector3f(resQuat.x, resQuat.y, resQuat.z);
            }

            // オイラー角からクォータニオンへの変換
            static Quaternion fromEuler(float roll, float pitch, float yaw) {
                float cy = cos(yaw * 0.5f);
                float sy = sin(yaw * 0.5f);
                float cp = cos(pitch * 0.5f);
                float sp = sin(pitch * 0.5f);
                float cr = cos(roll * 0.5f);
                float sr = sin(roll * 0.5f);

                return Quaternion(
                    sr * cp * cy - cr * sp * sy,
                    cr * sp * cy + sr * cp * sy,
                    cr * cp * sy - sr * sp * cy,
                    cr * cp * cy + sr * sp * sy
                );
            }

            // 単位クォータニオン
            static Quaternion identity() {
                return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
            }
        };
    }
}