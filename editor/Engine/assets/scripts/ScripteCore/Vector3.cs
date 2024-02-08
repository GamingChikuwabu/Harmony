namespace KALEIDOSCOPE
{
    namespace MATH
    {
        public struct Vector3
        {
            // 3次元ベクトルの各成分
            public float x, y, z;

            // コンストラクタ
            public Vector3(float x, float y, float z)
            {
                this.x = x;
                this.y = y;
                this.z = z;
            }

            // ベクトルの加算
            public static Vector3 operator +(Vector3 a, Vector3 b)
            {
                return new Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
            }

            // ベクトルの減算
            public static Vector3 operator -(Vector3 a, Vector3 b)
            {
                return new Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
            }

            // スカラー乗算
            public static Vector3 operator *(Vector3 a, float scalar)
            {
                return new Vector3(a.x * scalar, a.y * scalar, a.z * scalar);
            }

            // 単項マイナス演算子のオーバーロード
            public static Vector3 operator -(Vector3 a)
            {
                return new Vector3(-a.x, -a.y, -a.z);
            }

            // 内積
            public static double Dot(Vector3 a, Vector3 b)
            {
                return a.x * b.x + a.y * b.y + a.z * b.z;
            }

            // 外積
            public static Vector3 Cross(Vector3 a, Vector3 b)
            {
                return new Vector3(
                    a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x
                );
            }

            // 文字列表現
            public override string ToString()
            {
                return $"({x}, {y}, {z})";
            }
        }
    }
}