using System;

namespace KALEIDOSCOPE
{
    namespace MATH
    {
        public struct Quaternion
        {
            // �l�����̃R���|�[�l���g
            public double w, x, y, z;

            // �R���X�g���N�^
            public Quaternion(double _w, double _x, double _y, double _z)
            {
                w = _w;
                x = _x;
                y = _y;
                z = _z;
            }

            // Identity Quaternion �̃v���p�e�B
            public static Quaternion Identity
            {
                get { return new Quaternion(1, 0, 0, 0); }
            }

            // �l�����̉��Z
            public static Quaternion operator +(Quaternion a, Quaternion b)
            {
                return new Quaternion(a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z);
            }

            // �l�����̌��Z
            public static Quaternion operator -(Quaternion a, Quaternion b)
            {
                return new Quaternion(a.w - b.w, a.x - b.x, a.y - b.y, a.z - b.z);
            }

            // �l�����̏�Z
            public static Quaternion operator *(Quaternion a, Quaternion b)
            {
                return new Quaternion(
                    a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
                    a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
                    a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
                    a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w);
            }

            // �l�����̃m�����i�����j���v�Z
            public double Norm()
            {
                return Math.Sqrt(w * w + x * x + y * y + z * z);
            }

            // �l�����̐��K��
            public Quaternion Normalize()
            {
                var norm = Norm();
                return new Quaternion(w / norm, x / norm, y / norm, z / norm);
            }

            // ������\��
            public override string ToString()
            {
                return $"({w}, {x}, {y}, {z})";
            }
        }
    }
}
