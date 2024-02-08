using System;

namespace KALEIDOSCOPE
{
    namespace MATH
    {
        public struct Matrix4x4
        {
            // 4x4�̍s���񎟌��z��Œ��ڕێ�
            private double[,] elements;

            // �R���X�g���N�^
            public Matrix4x4(double[,] elements)
            {
                this.elements = elements;
            }

            // �w�肳�ꂽ�C���f�b�N�X�̗v�f���擾�܂��͐ݒ肷��
            public double this[int row, int column]
            {
                get { return elements[row, column]; }
                set { elements[row, column] = value; }
            }

            // �s��̉��Z
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

            // �s��̌��Z
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

            // �s��̏�Z
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

            // �s��̓]�u
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

            // �������e�s��𐶐�
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

            // ���s���e�s��𐶐�
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

            // ���s�ړ��s����쐬
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

            // �X�P�[�����O�s����쐬
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

            // �l�����Ɋ�Â���]�s����쐬
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

            // Identity Matrix �̃v���p�e�B
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