using KALEIDOSCOPE.MATH;


namespace KALEIDOSCOPE
{
    public class Transform : Component
    {
        public Vector3 position { get { return _position; } set { _position = value; } }
        public Vector3 scale { get { return _scale; } set { _scale = value; } }
        public Quaternion rotate { get { return _rotate; } set { _rotate = value; } }

        [SerializeField]
        private Vector3 _position;
        [SerializeField]
        private Vector3 _scale;
        [SerializeField]
        private Quaternion _rotate;

        // 親トランスフォームへの参照
        public Transform parent { get; set; }

        // コンストラクタ
        public Transform()
        {
            Debug.PrintDebugLog("Transform");
            position = new Vector3(0, 0, 0);
            scale = new Vector3(1, 1, 1);
            rotate = Quaternion.Identity;
        }

        // ローカルマトリクスを生成
        public Matrix4x4 GetLocalMatrix()
        {
            var translationMatrix = Matrix4x4.CreateTranslation(position);
            var scaleMatrix = Matrix4x4.CreateScale(_scale);
            var rotationMatrix = Matrix4x4.CreateFromQuaternion(_rotate);

            // マトリクスの乗算: Scale * Rotate * Translate
            return scaleMatrix * rotationMatrix * translationMatrix;
        }

        // ワールドマトリクスを生成
        public Matrix4x4 GetWorldMatrix()
        {
            var localMatrix = GetLocalMatrix();
            if (parent != null)
            {
                var parentMatrix = parent.GetWorldMatrix();
                return localMatrix * parentMatrix;
            }
            return localMatrix;
        }
    }
}