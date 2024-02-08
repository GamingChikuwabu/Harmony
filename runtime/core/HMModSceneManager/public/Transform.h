#pragma once
#include"Component.h"
#include"Eigen/Dense"

namespace HARMONY
{
    namespace CORE
    {
        class Transform : public Component
        {
        public:
            Transform();
            ~Transform();
            // セッター
            inline void setPosition(const Eigen::Vector3f& position) { _position = position; }
            inline void setScale(const Eigen::Vector3f& scale) { _scale = scale; }
            inline void setRotation(const Eigen::Quaternion<float>& rotation) { _rotate = rotation; }

            // ゲッタ
            inline Eigen::Vector3f getPosition() const { return _position; }
            inline Eigen::Vector3f getScale() const { return _scale; }
            inline Eigen::Quaternion<float> getRotation() const { return _rotate; }

            // ピッチ、ヨー、ロールからクォータニオンへの変換
            void setRotationFromPYR(float pitch, float yaw, float roll);

            // ワールド変換行列の計算
            Eigen::Matrix4f getWorldTransformMatrix() const;

            // 各要素を初期値に設定
            void reset();
        protected:
            Eigen::Vector3f             _position;
            Eigen::Vector3f             _scale;
            Eigen::Quaternion<float>    _rotate;
        };
    }
}