#pragma once
#include"Component.h"
#include"Utility.hpp"


namespace HARMONY
{
    namespace CORE
    {
        HMCLASS()
        class Transform : public Component
        {
            HM_MANUAL_REGISTER_DERIVED_CLASS_BODY(Transform,Component)
        public:
            Transform();
            ~Transform();
            // セッター
            inline void setPosition(const MATH::Vector3f& position) { _position = position; }
            inline void setScale(const MATH::Vector3f& scale) { _scale = scale; }
            inline void setRotation(const MATH::Quaternion& rotation) { _rotate = rotation; }

            // ゲッタ
            inline MATH::Vector3f getPosition() const { return _position; }
            inline MATH::Vector3f getScale() const { return _scale; }
            inline MATH::Quaternion getRotation() const { return _rotate; }

            // ピッチ、ヨー、ロールからクォータニオンへの変換
            void setRotationFromPYR(float pitch, float yaw, float roll);

            // ワールド変換行列の計算
            MATH::Matrix4x4 getWorldTransformMatrix() const;

            // 各要素を初期値に設定
            void reset();
        protected:
            HMPROPERTY()
            MATH::Vector3f             _position;
            HMPROPERTY()
            MATH::Vector3f             _scale;
            HMPROPERTY()
            MATH::Quaternion           _rotate;
        };
    }
} /// namespace HARMONY