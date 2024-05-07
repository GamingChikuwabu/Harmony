#include"Vector4f.h"
#include"Reflection.hpp"
#include"Macro/GenerateMacro.h"

namespace HARMONY
{
	namespace MATH
	{
		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(Vector4f)
			HM_ADD_PROPERTY_FLOAT(Vector4f, x),
			HM_ADD_PROPERTY_FLOAT(Vector4f, y),
			HM_ADD_PROPERTY_FLOAT(Vector4f, z),
			HM_ADD_PROPERTY_FLOAT(Vector4f, w),
		HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(Vector4f)
		Vector4f::Vector4f(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4f::Vector4f(const Vector4f& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}

		Vector4f::Vector4f()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		Vector4f Vector4f::operator+(const Vector4f& other)const
		{
			return Vector4f(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		Vector4f Vector4f::operator-(const Vector4f& other)const
		{
			return Vector4f(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		Vector4f Vector4f::operator*(const Vector4f& other)const
		{
			return Vector4f(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		Vector4f Vector4f::operator/(const Vector4f& other)const
		{
			return Vector4f(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		Vector4f Vector4f::operator+(float value)const
		{
			return Vector4f(x + value, y + value, z + value, w + value);
		}

		Vector4f Vector4f::operator-(float value)const
		{
			return Vector4f(x - value, y - value, z - value, w - value);
		}

		Vector4f Vector4f::operator*(float value)const
		{
			return Vector4f(x * value, y * value, z * value, w * value);
		}

		Vector4f Vector4f::operator/(float value)const
		{
			return Vector4f(x / value, y / value, z / value, w / value);
		}


		Vector4f& Vector4f::operator+=(const Vector4f& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		Vector4f& Vector4f::operator-=(const Vector4f& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		bool Vector4f::operator==(const Vector4f& v) const
		{
			if (x == v.x && y == v.y && z == v.z && w == v.w)
				return true;
			return false;
		}

		bool Vector4f::operator!=(const Vector4f& v) const
		{
			if (x != v.x || y != v.y || z != v.z || w != v.w)
				return true;
			return false;
		}

		float Vector4f::Dot(const Vector4f& v) const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		Vector4f Vector4f::Cross(const Vector4f& v) const
		{
			return Vector4f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, 0);
		}

		float Vector4f::Magnitude() const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}
		Vector4f Vector4f::Normalize() const
		{
			float mag = Magnitude();
			return Vector4f(x / mag, y / mag, z / mag, w / mag);
		}

		Vector4f Vector4f::Lerp(const Vector4f& v, float t) const
		{
			return Vector4f(x + (v.x - x) * t, y + (v.y - y) * t, z + (v.z - z) * t, w + (v.w - w) * t);
		}

		float Vector4f::Distance(const Vector4f& v) const
		{
			return sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y) + (z - v.z) * (z - v.z) + (w - v.w) * (w - v.w));
		}

		Vector4f Vector4f::Lerp(const Vector4f& a, const Vector4f& b, float t)
		{
			return a + (b - a) * t;
		}

		float Vector4f::Distance(const Vector4f& a, const Vector4f& b)
		{
			return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z) + (a.w - b.w) * (a.w - b.w));
		}

		Vector4f Vector4f::Normalize(const Vector4f& v)
		{
			float mag = v.Magnitude();
			return Vector4f(v.x / mag, v.y / mag, v.z / mag, v.w / mag);
		}

		Vector4f Vector4f::Zero()
		{
			return Vector4f(0, 0, 0, 0);
		}

		Vector4f Vector4f::One()
		{
			return Vector4f(1, 1, 1, 1);
		}

		Vector4f Vector4f::Up()
		{
			return Vector4f(0, 1, 0, 0);
		}

		float Vector4f::Dot(const Vector4f& a, const Vector4f& b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		}

		Vector4f Vector4f::Cross(const Vector4f& a, const Vector4f& b)
		{
			return Vector4f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, 0);
		}

		Vector4f Vector4f::Down()
		{

		}

		Vector4f Vector4f::Forward()
		{
			return Vector4f();
		}

		Vector4f Vector4f::Right()
		{
			return Vector4f();
		}
    }
}