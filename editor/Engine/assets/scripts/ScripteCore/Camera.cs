using KALEIDOSCOPE.MATH;

namespace KALEIDOSCOPE
{
    public class Camera : Behaviour
    {
        public enum ProjectionType
        {
            Perspective,  // �������e
            Orthographic  // ���s���e
        }

        public ProjectionType projectiontype { get; set; }
        [SerializeField]
        private float _fieldOfView = 60f;
        public float FieldOfView
        {
            get { return _fieldOfView; }
            set { _fieldOfView = value; }
        }

        [SerializeField]
        private float _aspectRatio = 16f / 9f;
        public float AspectRatio
        {
            get { return _aspectRatio; }
            set { _aspectRatio = value; }
        }

        [SerializeField]
        private float _nearClipPlane = 0.1f;
        public float NearClipPlane
        {
            get { return _nearClipPlane; }
            set { _nearClipPlane = value; }
        }

        [SerializeField]
        private float _farClipPlane = 1000f;
        public float FarClipPlane
        {
            get { return _farClipPlane; }
            set { _farClipPlane = value; }
        }

        [SerializeField]
        private float _height = 1080f;
        public float Height
        {
            get { return _height; }
            set { _height = value; }
        }

        [SerializeField]
        private float _width = 1920f;
        public float Width
        {
            get { return _width; }
            set { _width = value; }
        }


        public static Matrix4x4 GetViewMatrix(Vector3 position, Quaternion rotation)
        {
            // ��]�s����N�H�[�^�j�I�����琶��
            Matrix4x4 rotationMatrix = Matrix4x4.CreateFromQuaternion(rotation);

            // �ʒu�x�N�g���̋t�s��i���]�j
            Matrix4x4 translationMatrix = Matrix4x4.CreateTranslation(-position);

            // �r���[�s��́A��]�̋t�s��ƈʒu�̋t�s��̐�
            // �ʏ�A��]�̋t�s��͉�]�s��̓]�u�ɓ�����
            Matrix4x4 viewMatrix = Matrix4x4.Transpose(rotationMatrix) * translationMatrix;

            return viewMatrix;
        }

        // �v���W�F�N�V�����s��𐶐����郁�\�b�h
        public Matrix4x4 GetProjectionMatrix()
        {
            switch (projectiontype)
            {
                case ProjectionType.Perspective:
                    // �������e�̍s��𐶐�
                    return Matrix4x4.CreatePerspectiveFieldOfView(FieldOfView, AspectRatio, NearClipPlane, FarClipPlane);
                case ProjectionType.Orthographic:
                    // ���s���e�̍s��𐶐�
                    return Matrix4x4.CreateOrthographic(Width, Height, NearClipPlane, FarClipPlane);
            }
            return Matrix4x4.Identity;
        }
    }
}