#include"Transform.h"

namespace HARMONY
{
    namespace CORE
    {
        Transform::Transform()
        :_position(0.0f,0.0f,0.0f)
        ,_rotate(MATH::Quaternion::identity())
        ,_scale(0.0f,0.0f,0.0f)
        {
            
        }
        Transform::~Transform()
        {
        }

        void Transform::setRotationFromPYR(float pitch, float yaw, float roll)
        {
        }

        MATH::Matrix4x4 Transform::getWorldTransformMatrix() const
        {
            return MATH::Matrix4x4();
        }

        void Transform::reset()
        {
            
        }
    }
}