using System;

namespace KALEIDOSCOPE
{
    namespace MATH
    {
        public struct Matrix4x4
        {
            // 4x4の行列を二次元配列で直接保持
            private double[,] elements;

            // コンストラクタ
            public Matrix4x4(double[,] elements)
            {
                this.elements = elements;
            }

            // 指定されたインデックスの要素を取得または設定する
            public double this[int row, int column]
            {
                get { return elements[row, column]; }
                set { elements[row, column] = value; }
            }

            // 行列の加算
            public static Matrix4x4 operator +(Matrix4x4 a, Matrix4x4 b)
            {
                double[,] result = new double[4, 4];
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        result[i, j] = a[i, j] + b[i, j];
                    }
                }
                return new Matrix4x4(result);
            }

            // 行列の減算
            public static Matrix4x4 operator -(Matrix4x4 a, Matrix4x4 b)
            {
                double[,] result = new double[4, 4];
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        result[i, j] = a[i, j] - b[i, j];
                    }
                }
                return new Matrix4x4(result);
            }

            // 行列の乗算
            public static Matrix4x4 operator *(Matrix4x4 a, Matrix4x4 b)
            {
                double[,] result = new double[4, 4];
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        result[i, j] = 0;
                        for (int k = 0; k < 4; k++)
                        {
                            result[i, j] += a[i, k] * b[k, j];
                        }
                    }
                }
                return new Matrix4x4(result);
            }

            // 行列の転置
            public static Matrix4x4 Transpose(Matrix4x4 matrix)
            {
                double[,] result = new double[4, 4];
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        result[i, j] = matrix[j, i];
                    }
                }
                return new Matrix4x4(result);
            }

            // 透視投影行列を生成
            public static Matrix4x4 CreatePerspectiveFieldOfView(double fieldOfView, double aspectRatio, double nearPlane, double farPlane)
            {
                double f = 1.0 / Math.Tan(fieldOfView / 2.0);
                double rangeInv = 1.0 / (nearPlane - farPlane);

                double[,] result = new double[,] {
                        {f / aspectRatio, 0, 0, 0},
                        {0, f, 0, 0},
                        {0, 0, (nearPlane + farPlane) * rangeInv, nearPlane * farPlane * rangeInv * 2},
                        {0, 0, -1, 0}
                };

                return new Matrix4x4(result);
            }

            // 平行投影行列を生成
            public static Matrix4x4 CreateOrthographic(double width, double height, double nearPlane, double farPlane)
            {
                double[,] result = new double[,] {
                    {2.0 / width, 0, 0, 0},
                    {0, 2.0 / height, 0, 0},
                    {0, 0, 1.0 / (nearPlane - farPlane), nearPlane / (nearPlane - farPlane)},
                    {0, 0, 0, 1}
                };

                return new Matrix4x4(result);
            }

            // 平行移動行列を作成
            public static Matrix4x4 CreateTranslation(Vector3 pos)
            {
                double[,] result = new double[,] {
                    {1, 0, 0, pos.x},
                    {0, 1, 0, pos.y},
                    {0, 0, 1, pos.z},
                    {0, 0, 0, 1}
                };

                return new Matrix4x4(result);
            }

            // スケーリング行列を作成
            public static Matrix4x4 CreateScale(Vector3 scale)
            {
                double[,] result = new double[,] {
                    {scale.x, 0, 0, 0},
                    {0, scale.y, 0, 0},
                    {0, 0, scale.z, 0},
                    {0, 0, 0, 1}
                };
                return new Matrix4x4(result);
            }

            // 四元数に基づく回転行列を作成
            public static Matrix4x4 CreateFromQuaternion(Quaternion rotate)
            {
                double w = rotate.w, x = rotate.x, y = rotate.y, z = rotate.z;
                double xx = x * x, yy = y * y, zz = z * z;
                double xy = x * y, xz = x * z, yz = y * z;
                double wx = w * x, wy = w * y, wz = w * z;

                double[,] result = new double[,] {
                    {1 - 2 * (yy + zz), 2 * (xy - wz), 2 * (xz + wy), 0},
                    {2 * (xy + wz), 1 - 2 * (xx + zz), 2 * (yz - wx), 0},
                    {2 * (xz - wy), 2 * (yz + wx), 1 - 2 * (xx + yy), 0},
                    {0, 0, 0, 1}
                };

                return new Matrix4x4(result);
            }

            // Identity Matrix のプロパティ
            public static Matrix4x4 Identity
            {
                get
                {
                    return new Matrix4x4(new double[,] {
                        {1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}
                    });
                }
            }

        }
    }
}