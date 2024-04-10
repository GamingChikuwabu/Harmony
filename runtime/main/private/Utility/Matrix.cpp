#include"Matrix/Matrix4x4.h"


namespace HARMONY
{
	namespace MATH
	{
		Matrix4x4::Matrix4x4()
		:simd{_mm_setzero_ps(), _mm_setzero_ps(), _mm_setzero_ps(), _mm_setzero_ps() } 
		{

		}
		Matrix4x4::Matrix4x4(float m11, float m12, float m13, float m14,
					  float m21, float m22, float m23, float m24,
					  float m31, float m32, float m33, float m34,
					  float m41, float m42, float m43, float m44)
			: _m11(m11), _m12(m12), _m13(m13), _m14(m14),
			_m21(m21), _m22(m22), _m23(m23), _m24(m24),
			_m31(m31), _m32(m32), _m33(m33), _m34(m34),
			_m41(m41), _m42(m42), _m43(m43), _m44(m44)
		{

		}
	}
}