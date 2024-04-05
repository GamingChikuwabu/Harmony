#pragma once
#include<cmath>
#include"Macro/ObjectMacro.h"
#include"PlatformSimdchacker.h"
#include"Matrix4x4.generate.h"

namespace HARMONY 
{
    namespace MATH 
    {
        HMCLASS()
        struct UTILITY_API Matrix4x4 
        {
            HM_CLASS_BODY()
            union 
            {
                struct
                {
                    float _m11, _m12, _m13, _m14;
                    float _m21, _m22, _m23, _m24;
                    float _m31, _m32, _m33, _m34;
                    float _m41, _m42, _m43, _m44;
                };
                float m[4][4]; // 2次元配列でアクセスできるように追加
                __m128 simd[4]; // SIMDの配列
            };

            // デフォルトコンストラクタ
            Matrix4x4() : simd{ _mm_setzero_ps(), _mm_setzero_ps(), _mm_setzero_ps(), _mm_setzero_ps() } {}

            // パラメータ付きコンストラクタ
            Matrix4x4(float m11, float m12, float m13, float m14,
                      float m21, float m22, float m23, float m24,
                      float m31, float m32, float m33, float m34,
                      float m41, float m42, float m43, float m44)
                : _m11(m11), _m12(m12), _m13(m13), _m14(m14),
                _m21(m21), _m22(m22), _m23(m23), _m24(m24),
                _m31(m31), _m32(m32), _m33(m33), _m34(m34),
                _m41(m41), _m42(m42), _m43(m43), _m44(m44) {}

            // 行列の乗算オペレータ
            Matrix4x4 operator*(const Matrix4x4& rhs) const {
                Matrix4x4 result;
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        result.m[i][j] = m[i][0] * rhs.m[0][j] +
                            m[i][1] * rhs.m[1][j] +
                            m[i][2] * rhs.m[2][j] +
                            m[i][3] * rhs.m[3][j];
                    }
                }
                return result;
            }
            // 単位行列を生成
            static Matrix4x4 Identity() {
                return Matrix4x4(
                    1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f
                );
            }

            Matrix4x4 Transpose() const {
                Matrix4x4 result;
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        result.m[j][i] = this->m[i][j];
                    }
                }
                return result;
            }

            static Matrix4x4 Scaling(float sx, float sy, float sz) {
                return Matrix4x4(
                    sx, 0.0f, 0.0f, 0.0f,
                    0.0f, sy, 0.0f, 0.0f,
                    0.0f, 0.0f, sz, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f
                );
            }

            static Matrix4x4 Translation(float tx, float ty, float tz) {
                return Matrix4x4(
                    1.0f, 0.0f, 0.0f, tx,
                    0.0f, 1.0f, 0.0f, ty,
                    0.0f, 0.0f, 1.0f, tz,
                    0.0f, 0.0f, 0.0f, 1.0f
                );
            }

            // X軸周りに回転する行列を生成
            static Matrix4x4 RotationX(float radians) {
                float cosTheta = cos(radians);
                float sinTheta = sin(radians);
                return Matrix4x4(
                    1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, cosTheta, -sinTheta, 0.0f,
                    0.0f, sinTheta, cosTheta, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f
                );
            }

            static Matrix4x4 RotationY(float radians) {
                float cosTheta = cos(radians);
                float sinTheta = sin(radians);
                return Matrix4x4(
                    cosTheta, 0.0f, sinTheta, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    -sinTheta, 0.0f, cosTheta, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f
                );
            }

            static Matrix4x4 RotationZ(float radians) {
                float cosTheta = cos(radians);
                float sinTheta = sin(radians);
                return Matrix4x4(
                    cosTheta, -sinTheta, 0.0f, 0.0f,
                    sinTheta, cosTheta, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f
                );
            }
        };
    } // namespace MATH
} // namespace HARMONY