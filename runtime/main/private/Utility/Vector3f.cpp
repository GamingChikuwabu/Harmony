#include"Vector3f.h"
#include"Reflection.hpp"
#include"Macro/GenerateMacro.h"

namespace HARMONY 
{
    namespace MATH 
    {

        HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(Vector3f)
            HM_ADD_PROPERTY_FLOAT(Vector3f, x),
            HM_ADD_PROPERTY_FLOAT(Vector3f, y),
            HM_ADD_PROPERTY_FLOAT(Vector3f, z)
        HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(Vector3f)

        // コンストラクタの実装
        Vector3f::Vector3f(float _x, float _y, float _z) : simd(_mm_set_ps(0, _z, _y, _x)) {}

        // 加算のオペレータオーバーロード
        Vector3f Vector3f::operator+(const Vector3f& other) const {
            return Vector3f(_mm_add_ps(this->simd, other.simd));
        }

        // 減算のオペレータオーバーロード
        Vector3f Vector3f::operator-(const Vector3f& other) const {
            return Vector3f(_mm_sub_ps(this->simd, other.simd));
        }

        // スカラー乗算のオペレータオーバーロード
        Vector3f Vector3f::operator*(float scalar) const {
            __m128 scalarVector = _mm_set1_ps(scalar);
            return Vector3f(_mm_mul_ps(this->simd, scalarVector));
        }

        // 内積の静的メソッド
        float Vector3f::dot(const Vector3f& a, const Vector3f& b) {
            __m128 mul = _mm_mul_ps(a.simd, b.simd);
            __m128 shuf = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(1, 0, 3, 2));
            __m128 sums = _mm_add_ps(mul, shuf);
            shuf = _mm_movehl_ps(shuf, sums);
            sums = _mm_add_ss(sums, shuf);
            return _mm_cvtss_f32(sums);
        }

        // 外積の静的メソッド
        Vector3f Vector3f::cross(const Vector3f& a, const Vector3f& b) {
            return Vector3f(
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
            );
        }

        // 長さの計算
        float Vector3f::length() const {
            __m128 mul = _mm_mul_ps(this->simd, this->simd);
            __m128 shuf = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 1, 0, 3));
            __m128 sums = _mm_add_ps(mul, shuf);
            shuf = _mm_movehl_ps(shuf, sums);
            sums = _mm_add_ss(sums, shuf);
            return _mm_cvtss_f32(_mm_sqrt_ss(sums));
        }

    } // namespace MATH
} // namespace HARMONY