#include"Transform.h"

namespace HARMONY
{
    namespace CORE
    {
        Transform::Transform()
        {
            //reset();
        }
        Transform::~Transform()
        {
        }
        //void Transform::setRotationFromPYR(float pitch, float yaw, float roll)
        //{
        //    // オイラー角からクォータニオンへの変換
        //    _rotate = Eigen::AngleAxisf(roll, Eigen::Vector3f::UnitZ())
        //        * Eigen::AngleAxisf(pitch, Eigen::Vector3f::UnitX())
        //        * Eigen::AngleAxisf(yaw, Eigen::Vector3f::UnitY());
        //}
        //Eigen::Matrix4f Transform::getWorldTransformMatrix() const
        //{
        //    Eigen::Matrix4f transformMatrix = Eigen::Matrix4f::Identity();
        //    // スケール、回転、位置を組み合わせる
        //    transformMatrix.block<3, 3>(0, 0) = _rotate.toRotationMatrix() * _scale.asDiagonal();
        //    transformMatrix.block<3, 1>(0, 3) = _position;
        //    return transformMatrix;
        //}

        //void Transform::reset()
        //{
        //    _position = Eigen::Vector3f(0.0f, 0.0f, 0.0f); // 位置を原点に設定
        //    _scale = Eigen::Vector3f(1.0f, 1.0f, 1.0f);    // スケールを等倍に設定
        //    _rotate = Eigen::Quaternion<float>::Identity(); // 回転を無回転に設定
        //}
    }
}