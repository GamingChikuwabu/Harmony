using System;

namespace KALEIDOSCOPE
{
    namespace MATH
    {
        public struct Quaternion
        {
            // 四元数のコンポーネント
            public double w, x, y, z;

            // コンストラクタ
            public Quaternion(double _w, double _x, double _y, double _z)
            {
                w = _w;
                x = _x;
                y = _y;
                z = _z;
            }

            // Identity Quaternion のプロパティ
            public static Quaternion Identity
            {
                get { return new Quaternion(1, 0, 0, 0); }
            }

            // 四元数の加算
            public static Quaternion operator +(Quaternion a, Quaternion b)
            {
                return new Quaternion(a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z);
            }

            // 四元数の減算
            public static Quaternion operator -(Quaternion a, Quaternion b)
            {
                return new Quaternion(a.w - b.w, a.x - b.x, a.y - b.y, a.z - b.z);
            }

            // 四元数の乗算
            public static Quaternion operator *(Quaternion a, Quaternion b)
            {
                return new Quaternion(
                    a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
                    a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
                    a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
                    a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w);
            }

            // 四元数のノルム（長さ）を計算
            public double Norm()
            {
                return Math.Sqrt(w * w + x * x + y * y + z * z);
            }

            // 四元数の正規化
            public Quaternion Normalize()
            {
                var norm = Norm();
                return new Quaternion(w / norm, x / norm, y / norm, z / norm);
            }

            // 文字列表現
            public override string ToString()
            {
                return $"({w}, {x}, {y}, {z})";
            }
        }
    }
}
