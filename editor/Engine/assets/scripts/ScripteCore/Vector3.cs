namespace KALEIDOSCOPE
{
    namespace MATH
    {
        public struct Vector3
        {
            // 3�����x�N�g���̊e����
            public float x, y, z;

            // �R���X�g���N�^
            public Vector3(float x, float y, float z)
            {
                this.x = x;
                this.y = y;
                this.z = z;
            }

            // �x�N�g���̉��Z
            public static Vector3 operator +(Vector3 a, Vector3 b)
            {
                return new Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
            }

            // �x�N�g���̌��Z
            public static Vector3 operator -(Vector3 a, Vector3 b)
            {
                return new Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
            }

            // �X�J���[��Z
            public static Vector3 operator *(Vector3 a, float scalar)
            {
                return new Vector3(a.x * scalar, a.y * scalar, a.z * scalar);
            }

            // �P���}�C�i�X���Z�q�̃I�[�o�[���[�h
            public static Vector3 operator -(Vector3 a)
            {
                return new Vector3(-a.x, -a.y, -a.z);
            }

            // ����
            public static double Dot(Vector3 a, Vector3 b)
            {
                return a.x * b.x + a.y * b.y + a.z * b.z;
            }

            // �O��
            public static Vector3 Cross(Vector3 a, Vector3 b)
            {
                return new Vector3(
                    a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x
                );
            }

            // ������\��
            public override string ToString()
            {
                return $"({x}, {y}, {z})";
            }
        }
    }
}